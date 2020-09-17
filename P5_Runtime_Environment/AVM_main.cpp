#include "AVM.h"
#include <fstream>
#define BON "\e[1m"
#define BOFF "\e[0m"

int main(int argc, char ** argv){
    std::ifstream ifs;
    error_handler_init("AVM");
    if (argc > 1) {
        ifs.open(argv[1],  std::ios::in | std::ios::binary);
        if (!ifs.is_open()) {
            //fprintf(stderr, "Unable to open input file \n");
            error(ErrorType::FatalError, 0, "Could not load program " BON "\'%s\'" BOFF "\n", argv[1]);
            return 1;
        }
    } else {
        error(ErrorType::FatalError, 0, "Usage: avm <filename>\n");
        return 1;
    }
    AVM vm = AVM(ifs);
    vm.execute();
    error_handler_destroy();
    ifs.close();
    return 0;
}