#include <rf/universe.hh>
#include <raylib.h>
#include <ctime>
#include <random>
#include <stdexcept>

size_t WIDTH = 1366;
size_t HEIGHT = 768;
size_t RADIUS = 80;
size_t NUMBER_OF_PARTICLES = 2000;

bool DONT_PLAY = false;
bool TELL_HELP = false;
std::string INPUT_MAT = "";
std::string OUTPUT_MAT = "";

rf::Universe* UNIVERSE = nullptr;

void InitUniverse() {
    UNIVERSE = new rf::Universe(WIDTH, HEIGHT, RADIUS);
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
        UNIVERSE->dumpMatterFromFile(OUTPUT_MAT);
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
    char* msg = 
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
    " -P                        dont play particles\n"
    " --help                    show help screen\n";
    std::printf("%s", msg);
}

void AddStringArgument(int argc, char** args,
                       size_t& i, char* flag,
                       char* varname, std::string& target) {
    if (std::strcmp(args[i], flag)) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        i++;
        target = std::string(args[i+1]);
        i++;
    }
}

void AddIntegerArgument(int argc, char** args,
                        size_t& i, char* flag,
                        char* varname, size_t& target) {
    if (std::strcmp(args[i], flag)) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        i++;
        target = std::stoi(std::string(args[i+1]));
        i++;
    }
}

void AddBooleanArgument(int argc, char** args,
                        size_t& i, char* flag,
                        bool& target) {
    if (std::strcmp(args[i], flag)) {
        if (i + 1 >= argc) {
            throw std::runtime_error("syntax of `" +
                                     flag + "`: " +
                                     flag + " <" +
                                     varname + ">");
        }
        target = true;
        i++;
    }
}

void ProcessArguments(int argc, char** args) {
    size_t i = 0;
    while(i < args) {
        AddStringArgument(argc, args, i, "-i", "mat-file-path", INPUT_MAT);
        AddStringArgument(argc, args, i, "-o", "mat-file-path", INPUT_MAT);

        AddIntegerArgument(argc, args, i, "-w", "screen-width", WIDTH);
        AddIntegerArgument(argc, args, i, "-h", "screen-height", HEIGHT);
        
        AddIntegerArgument(argc, args, i, "-p", "particle-number", PARTICLES);
        AddIntegerArgument(argc, args, i, "-r", "gravity-radius", RADIUS);

        AddBooleanArgument(argc, args, i, "-P", DONT_PLAY);
        AddBooleanArgument(argc, args, i, "--help", TELL_HELP);
    }

    if (TELL_HELP) {
        TellHelp();
        std::exit(0);
    }
}

int main(int argc, char** args) {
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
        if(IsKeyDown(KEY_SPACE))
            StepUniverse();
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
}
