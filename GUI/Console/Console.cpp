// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Console.h"

#include "Application.h"

Console::Console(Application &ref) :

Layer(ref), view(ref.window), cursor(ref.window)
{
    // Initialize the text storage
    storage.push_back("");

    // Initialize the input buffer
    input.push_back("");
}

Console::~Console()
{
}

void
Console::init()
{
    Layer::init();
 
    // Initialize layout parameters
    padx     = app.window.scale * 5;
    pady     = app.window.scale * 2;
    fontSize = app.window.scale * 14;
    lineSkip = app.window.scale * 5;
    
    // Get the maximum screen dimensions
    mm::DisplayMode mode = mm::DisplayMode(0);
    printf("Creating console texture: %dx%d\n", mode.width(), mode.height());
    
    // Create the render view
    view.init(mode.width(), mode.height());
    
    // Load the console font
    consoleFont = app.fonts.get(FontID::console, fontSize);
    glyphWidth = consoleFont.width("A");

    // Create the cursor
    cursor.init(glyphWidth + 2, fontSize + 3,
                mm::Color(0xFF,0xFF,0xFF,0x80), mm::Color(0xFF,0xFF,0xFF,0x80),
                mm::Color(0xFF,0xFF,0xFF,0x80), mm::Color(0xFF,0xFF,0xFF,0x80));
    
    // Print intro message
    *this << "Retro shell 0.1, ";
    *this << "Dirk W. Hoffmann, ";
    *this << __DATE__ << " " << __TIME__ << "." << '\n';
    *this << "Linked to vAmiga core ";
    *this << V_MAJOR << '.' << V_MINOR << '.' << V_SUBMINOR << '.' << '\n' << '\n';

    printHelp();
    *this << '\n';
    printPrompt();
}

void
Console::configure()
{
    
}

void
Console::update(i64 frame, mm::Time dt)
{
    Layer::update(dt);
    
    if (frame % 32 == 0) {
        cursor.setAlpha(frame % 64 ? 0xFF : 0x00);
        isDirty = true;
    }
    
    if (isDirty) {
        
        updateTexture();
        isDirty = false;
    }
}

void
Console::render()
{
    if (isVisible()) {
        
        if (isDirty) {
            updateTexture();
            isDirty = false;
        }
        view.render();
    }
}

void
Console::respond(mm::Event &event)
{
    switch (event.type()) {
            
        case SDL_KEYDOWN:
            respondToKeyboardEvent(event);
            if (doubleTab) doubleTab--;
            break;
            
        case SDL_TEXTINPUT:
            type(event.opaque().text.text[0]);
            if (doubleTab) doubleTab--;
            break;
            
        case SDL_MOUSEWHEEL:
            scroll((float)event.opaque().wheel.y);
            break;
            
        default:
            break;
    }
}

void
Console::respondToKeyboardEvent(mm::Event &event)
{
    auto keyboardEvent = mm::KeyboardEvent(event);
    
    switch (keyboardEvent.opaque()->keysym.sym) {
            
        case SDLK_RETURN:

            *this << '\n';
                        
            // Print a help message if no input is given
            if (input[ipos].empty()) {
                printHelp();
                printPrompt();
                break;
            }

            // Add the current input line to the user input history
            input[input.size() - 1] = input[ipos];

            // Create a new input line
            input.push_back("");
            ipos = (int)input.size() - 1;

            // Execute the command
            exec(input[ipos - 1]);
            
            makeLastLineVisible();
            break;
            
        case SDLK_BACKSPACE:
            
            if (cpos > 0) {
                input[ipos].erase(input[ipos].begin() + --cpos);
            }
            *this << '\r' << string(prompt) << input[ipos];
            
            makeLastLineVisible();
            break;
            
        case SDLK_TAB:
            
            if (doubleTab) {
                
                printf("Double TAB\n");
                
                *this << '\n';

                // Print the instructions for this command
                interpreter.help(input[ipos]);
                
                // Repeat the old input string
                *this << string(prompt) << input[ipos];
                
            } else {
                
                interpreter.autoComplete(input[ipos]);
                cpos = (int)input[ipos].length();
                replace(input[ipos]);
            }
            
            doubleTab = 2;
            makeLastLineVisible();
            break;
                
        case SDLK_UP:
            
            printf("SDLK_UP\n");
            if (ipos > 0) {
                ipos--;
                cpos = (int)input[ipos].size();
                
                replace(input[ipos]);
            }
            makeLastLineVisible();
            break;
            
        case SDLK_DOWN:
            
            printf("SDLK_DOWN\n");
            if (ipos < input.size() - 1) {
                ipos++;
                cpos = (int)input[ipos].size();
                
                replace(input[ipos]);
            }
            makeLastLineVisible();
            break;
            
        case SDLK_LEFT:
            
            printf("SDLK_LEFT\n");
            if (cpos > 0) {
                cpos--;
            }
            makeLastLineVisible();
            break;
            
        case SDLK_RIGHT:
            
            printf("SDLK_RIGHT\n");
            if (cpos < input[ipos].length()) {
                cpos++;
            }
            makeLastLineVisible();
            break;
            
        case SDLK_HOME:
            
            printf("SDLK_HOME\n");
            cpos = 0;
            makeLastLineVisible();
            break;
            
        case SDLK_END:
            
            printf("SDLK_END\n");
            cpos = (int)input[ipos].length();
            makeLastLineVisible();
            break;
            
        case SDLK_PAGEUP:
            
            printf("SDLK_PAGEUP\n");
            scrollUp(numRows);
            break;
            
        case SDLK_PAGEDOWN:
            
            printf("SDLK_PAGEDOWN\n");
            scrollDown(numRows);
            break;
            
        default:
            return;
    }
    
    isDirty = true;
}

void
Console::type(char c)
{
    if (isprint(c)) {
        
        if (input[ipos].length() < numCols - (int)prompt.length() - 1) {
            
            input[ipos].insert(input[ipos].begin() + cpos++, c);
        }
        *this << '\r' << string(prompt) << input[ipos];
        
        makeLastLineVisible();
        isDirty = true;
    }
}

void
Console::resize(int width, int height)
{
    setNumRows((height - 2 * pady) / (fontSize + lineSkip));
    setNumCols((width - 2 * padx) / glyphWidth);
    
    printf("Rows: %d, Columns: %d\n", numRows, numCols);
    
    isDirty = true;
}

void
Console::alphaDidChange()
{
    view.setAlpha(alpha);
}

void
Console::setNumRows(int value)
{
    value = MIN(value, 255);

    numRows = value;
    isDirty = true;
}

void
Console::setNumCols(int value)
{
    numCols = value;
    isDirty = true;
}

void
Console::clear()
{
    scrollTo(65536);
}

void
Console::printHelp()
{
    *this << "Press 'TAB' twice for help." << '\n';
}

void
Console::printPrompt()
{
    // Finish the current line (if neccessary)
    if (!lastLine().empty()) *this << '\n';

    // Print the prompt
    *this << prompt;
}

Console&
Console::operator<<(char value)
{
    if (value == '\n') {

        // Newline (appends an empty line)
        storage.push_back("");

    } else if (value == '\r') {

        // Carriage return (clears the current line)
        storage.back() = "";
        
    } else {
        
        // Add a single character
        if (storage.back().length() >= numCols) storage.push_back("");
        storage.back() += value;
    }
    
    shorten();
    return *this;
}

Console&
Console::operator<<(const std::string& text)
{
    size_t remaining = numCols - storage.back().length();
    
    // Split the string if it is too large
    if (text.length() > remaining) {
        *this << text.substr(0, remaining) << '\n' << text.substr(remaining);
    } else {
        storage.back() += text;
    }
    
    shorten();
    isDirty = true;
    return *this;
}

Console&
Console::operator<<(int value)
{
    *this << std::to_string(value);
    return *this;
}

Console&
Console::operator<<(long value)
{
    *this << std::to_string(value);
    return *this;
}

void
Console::shorten()
{
    while (storage.size() > 600) {
        
        storage.erase(storage.begin());
        scrollUp(1);
    }
}

void
Console::tab(int hpos)
{
    int delta = hpos - (int)storage.back().length();
    for (int i = 0; i < delta; i++) {
        *this << ' ';
    }
}


void
Console::replace(const string& text, const string& prefix)
{
    
    storage.back() = prefix + text.substr(0, numCols);
}

void
Console::list()
{
    for (int i = 0; i < (int)input.size(); i++) {
        printf("%d: %s\n", i, input[i].c_str());
    }
}

void
Console::scrollTo(int line)
{
    line = std::clamp(line, 0, (int)storage.size() - 1);
        
    isDirty = line != vpos;
    vpos = line;
}

void
Console::makeLastLineVisible()
{    
    if (!lastLineIsVisible()) {
        scrollTo((int)storage.size() - numRows);
    }
}

int
Console::rowOfLastLine()
{
    return (int)storage.size() - vpos - 1;
}

bool
Console::lastLineIsVisible()
{
    return rowOfLastLine() >= 0 && rowOfLastLine() < numRows;
}

void
Console::scroll(float delta)
{
    printf("scroll: %f\n", delta);
    
    static float vpos = 0.0;
    
    float newpos = vpos + delta;
    int dy = (int)abs(newpos);
    
    if (dy >= 1) {
        if (newpos > 0) { scrollUp(dy); newpos -= dy; }
        if (newpos < 0) { scrollDown(dy); newpos += dy; }
    }
}

bool
Console::exec(const string &command, bool verbose)
{
    bool success = false;
    
    // Print the command string if requested
    if (verbose) *this << command << '\n';
        
    printf("Command: %s\n", command.c_str());
    
    try {
        
        // Hand the command over to the intepreter
        interpreter.exec(command);
        success = true;
               
    } catch (TooFewArgumentsError &err) {
        *this << err.what() << ": Too few arguments";
        *this << '\n';
        
    } catch (TooManyArgumentsError &err) {
        *this << err.what() << ": Too many arguments";
        *this << '\n';
        
    } catch (ParseEnumError &err) {
        *this << err.token << ": Invalid key" << '\n';
        *this << "Expected: " << err.expected << '\n';
        
    } catch (ParseBoolError &err) {
        *this << "Invalid key" << '\n';
        *this << "Expected: true or false" << '\n';

    } catch (ParseError &err) {
        *this << err.what() << ": Syntax error";
        *this << '\n';
        // *this << "Expected: " << err.what() << '\n';
        
    } catch (ConfigUnsupportedError) {
        *this << "This option is not yet supported.";
        *this << '\n';
        
    } catch (ConfigLockedError &err) {
        *this << "This option is locked because the Amiga is powered on.";
        *this << '\n';
        
    } catch (ConfigArgError &err) {
        *this << "Error: Invalid argument. Expected: " << err.what();
        *this << '\n';
        
    } catch (ConfigFileReadError &err) {
        *this << "Error: Unable to read file " << err.what();
        *this << '\n';
        
    } catch (VAError &err) {
        *this << err.what();
        *this << '\n';
    }
    
    // Print a new prompt
    // printf("Command: %s\n", command.c_str());
    // *this << string(prompt);
    printPrompt();
    cpos = 0;
    
    return success;
}

void
Console::exec(std::istream &stream)
{
    int line = 0;
    string command;
        
    while(std::getline(stream, command)) {

        line++;
        printf("Line %d: %s\n", line, command.c_str());

        // Skip empty lines
        if (command == "") continue;

        // Skip comments
        if (command.substr(0,1) == "#") continue;
        
        // Execute the command
        if (!exec(command, true)) {
            throw Exception(command, line);
        }
    }
}

void
Console::updateTexture()
{
    view.clear(mm::Color(0x21, 0x21, 0x21, 0xD0));
    
    // Instantiate missing text objects
    for (int i = (int)text.size(); i < numRows; i++) {
        text.push_back(mm::TextView(app.window));
        mm::TextView &ref = text.back();
        ref.setFont(consoleFont);
        ref.setColor(mm::Color::White);
        ref.setPosition(0, 0, hposForCol(0), vposForRow(i));
    }
    
    // Draw all text rows
    for (int i = 0; i < numRows; i++) {
        if (vpos + i < storage.size()) {
            text[i].setString(storage[vpos + i]);
        } else {
            text[i].setString("");
        }
        text[i].render(view.getTexture());
    }
    
    // Draw cursor
    int cursorX = hposForCol(cpos + (int)prompt.length());
    int cursorY = vposForRow(rowOfLastLine()) + 3;
    cursor.setPosition(0, 0, cursorX, cursorY);
    cursor.render(view.getTexture());
}
