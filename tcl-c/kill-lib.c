//based on
//http://www.democritos.it/activities/IT-MC/talks/tcl-c.pdf

//creates a command that can be exexuted in the interpretator - tclsh
//compile with
// gcc -c -Wall -fpic kill-lib.c
// gcc -shared -o killtcl.so kill-lib.o -ltcl
// and load into tclsh
//> load ./killtcl.so
//> kill [process id] [signal]
#include <tcl.h>
#include <signal.h>

int TclKill(ClientData clientData, Tcl_Interp *interp, int arg_count, Tcl_Obj *CONST args[])
{
    int pid;
    int signal;

    if(arg_count != 3) {
        Tcl_WrongNumArgs(interp, 1, args, "pid signal");
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, args[1],&pid) != TCL_OK ||
       Tcl_GetIntFromObj(interp, args[2],&signal) != TCL_OK) {
      return TCL_ERROR;
    }

    if(kill(pid,signal) < 0) {
        Tcl_AppendResult(interp, "Error in kill", Tcl_PosixError(interp), NULL);
        return TCL_ERROR;
    }

    return TCL_OK;
}

int Killtcl_Init(Tcl_Interp *interp)
{
    Tcl_CreateObjCommand(interp, "kill", TclKill, NULL, (Tcl_CmdDeleteProc *)NULL);
    return TCL_OK;
}

int Killtcl_SafeInit(Tcl_Interp *interp)
{
    //TODO add code for safe initialization
    return TCL_OK;
}

int Killtcl_Unload(Tcl_Interp *interp)
{
    //TODO add code for unloading
    return TCL_OK;
}

int Killtcl_SafeUnload(Tcl_Interp *interp)
{
    //TODO add code for safe unloading
    return TCL_OK;
}
