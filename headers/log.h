#define DEBUG 1

enum status {game, solver, info, debug, warning, error};
typedef enum status status;

const char* getStatusChar(enum status sta);

void printLog(status sta, const char* str, ...);

void initLog();