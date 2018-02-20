#include "ArgsScreen.h"

#include "config.h"
#include "CRT.h"
#include "IncSet.h"
#include "ListItem.h"
#include "Platform.h"
#include "StringUtils.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*{
#include "InfoScreen.h"

typedef struct ArgsScreen_ {
   InfoScreen super;
} ArgsScreen;
}*/

InfoScreenClass ArgsScreen_class = {
   .super = {
      .extends = Class(Object),
      .delete = ArgsScreen_delete
   },
   .scan = ArgsScreen_scan,
   .draw = ArgsScreen_draw
};

ArgsScreen* ArgsScreen_new(Process* process) {
   ArgsScreen* this = xMalloc(sizeof(ArgsScreen));
   Object_setClass(this, Class(ArgsScreen));
   return (ArgsScreen*) InfoScreen_init(&this->super, process, NULL, LINES-3, " ");
}

void ArgsScreen_delete(Object* this) {
   free(InfoScreen_done((InfoScreen*)this));
}

void ArgsScreen_draw(InfoScreen* this) {
   InfoScreen_drawTitled(this, "Arguments of process %d - %s", this->process->pid, this->process->comm);
}

void ArgsScreen_scan(InfoScreen* this) {
   Panel* panel = this->display;
   int idx = MAX(Panel_getSelectedIndex(panel), 0);

   Panel_prune(panel);

   CRT_dropPrivileges();
   char* args = Platform_getProcessArgs(this->process->pid);
   CRT_restorePrivileges();
   if (args) {
      for (char *p = args; *p; p = strrchr(p, 0)+1)
         InfoScreen_addLine(this, p);
      free(args);
   }
   else {
      InfoScreen_addLine(this, "Could not read process arguments.");
   }
   Panel_setSelected(panel, idx);
}
