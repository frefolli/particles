#include <rf/universe.hh>
#include <raylib.h>
#include <ctime>
#include <cstring>
#include <random>
#include <stdexcept>

size_t WIDTH = 1366;
size_t HEIGHT = 768;
size_t RADIUS = 80;
size_t NUMBER_OF_PARTICLES = 2000;
float SPEED = 1.0F;

bool DONT_PLAY = false;
bool TELL_HELP = false;
bool PAUSE = false;
std::string INPUT_MAT = "";
std::string OUTPUT_MAT = "";

rf::Universe* UNIVERSE = nullptr;

void InitUniverse() {
    UNIVERSE = new rf::Universe(WIDTH, HEIGHT, RADIUS, SPEED);
    if (UNIVERSE == nullptr)
        throw std::runtime_error("NullPointerException");
}

void LoadMatter() {
    if (INPUT_MAT.size())
        UNIVERSE->loadMatterFromFile(INPUT_MAT);
    else
        UNIVERSE->randomMatter();
}

void DumpMatter() {
    if (OUTPUT_MAT.size())
        UNIVERSE->dumpMatterToFile(OUTPUT_MAT);
}

void FillUniverse() {
    UNIVERSE->addParticles(NUMBER_OF_PARTICLES);
}

void StepUniverse() {
    UNIVERSE->step();
}

void DrawUniverse() {
    UNIVERSE->draw();
}

void CloseUniverse() {
    delete UNIVERSE;
    UNIVERSE = nullptr;
}

void TellHelp() {
    const char* msg = 
    "dioimperatoresalvini [-i] [-o] [-h] [-w] [-p] [-r] [-P] [--help]\n"
    "\n"
    "   particles simulation\n"
    "\n"
    " -i <mat-file-path>        input path of mat file\n"
    " -o <mat-file-path>        output path of mat file\n"
    " -h <screen-height>        screen height\n"
    " -w <screen-width>         screen width\n"
    " -p <particle-number>      number of particles\n"
    " -r <radius>               gravity radius\n"
    " -s <simulation-speed>     velocity delta factor\n"
    " -P                        dont play particles\n"
    " --help                    show help screen\n";
    std::printf("%s", msg);
}

int AddStringArgument(size_t argc, char** args,
                       size_t& i, std::string flag,
                       std::string varname, std::string& target) {
    if (std::strcmp(args[i], flag.c_str()) == 0) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        i++;
        target = std::string(args[i]);
        i++;
        return 1;
    }
    return 0;
}

int AddIntegerArgument(size_t argc, char** args,
                        size_t& i, std::string flag,
                        std::string varname, size_t& target) {
    if (std::strcmp(args[i], flag.c_str()) == 0) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        i++;
        target = std::stoi(std::string(args[i]));
        i++;
        return 1;
    }
    return 0;
}

int AddFloatArgument(size_t argc, char** args,
                     size_t& i, std::string flag,
                     std::string varname, float& target) {
    if (std::strcmp(args[i], flag.c_str()) == 0) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        i++;
        target = std::stof(std::string(args[i]));
        i++;
        return 1;
    }
    return 0;
}

int AddBooleanArgument(char** args,
                        size_t& i, std::string flag,
                        bool& target) {
    if (std::strcmp(args[i], flag.c_str()) == 0) {
        target = true;
        i++;
        return 1;
    }
    return 0;
}

void ProcessArguments(size_t argc, char** args) {
    size_t i = 1;
    while(i < argc) {
        if (
            !(AddStringArgument(argc, args, i, "-i", "mat-file-path", INPUT_MAT)) &&
            !(AddStringArgument(argc, args, i, "-o", "mat-file-path", OUTPUT_MAT)) &&

            !(AddIntegerArgument(argc, args, i, "-w", "screen-width", WIDTH)) &&
            !(AddIntegerArgument(argc, args, i, "-h", "screen-height", HEIGHT)) &&
            
            !(AddIntegerArgument(argc, args, i, "-p", "particle-number", NUMBER_OF_PARTICLES)) &&
            !(AddIntegerArgument(argc, args, i, "-r", "gravity-radius", RADIUS)) &&
            !(AddFloatArgument(argc, args, i, "-s", "simulation-speed", SPEED)) &&

            !(AddBooleanArgument(args, i, "-P", DONT_PLAY)) &&
            !(AddBooleanArgument(args, i, "--help", TELL_HELP))
        ) {
            throw std::runtime_error("unidentified flag: " + std::string(args[i]));
        }
    }

    if (TELL_HELP) {
        TellHelp();
        std::exit(0);
    }
}

int realMain(int argc, char** args) {
    // --------------------------------------------------------------------
    // INIT
    ProcessArguments(argc, args);
    std::srand(time(NULL));
    InitUniverse();
    LoadMatter();
    DumpMatter();
    if (DONT_PLAY) {
        std::exit(0);
    }
    FillUniverse();
    // --------------------------------------------------------------------
    // INIT WINDOW
    InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
    SetTargetFPS(60);
    // --------------------------------------------------------------------
    // REL
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_LEFT)) {
            PAUSE = !PAUSE;
        } else if (PAUSE) {
            StepUniverse();
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawUniverse();
        EndDrawing();
    }
    // --------------------------------------------------------------------
    // DELETE
    CloseUniverse();
    // --------------------------------------------------------------------
    CloseWindow();
    return 0;
}

int main(int argc, char** args) {
    char* AC_RED = "\u001b[31m";
    char* AC_RESET = "\u001b[0m";
    try {
        return realMain(argc, args);
    } catch(std::exception& error) {
        std::printf("%sERROR:%s %s\n", AC_RED, AC_RESET, error.what());
        return 1;
    }
}
