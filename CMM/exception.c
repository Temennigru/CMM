#include <stdarg.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "exception.h"

Bool was_try__ = FALSE;

const char* _ErrorMessage[] = {
	"%s",
	"Error: Index is out of range.",
	"Error: Container is empty.",
	"Error: New matrix size is not greater than current one.",
	"Error: Index or size cannot be negative.",
	"Error: Method option is not within permissible options.",
	"Error: File could not be found or created.",
	"Error: There was not enough memory to allocate container.",
	"Error: The resource being freed was not locked."
			   }; // Error code list

void ThrowException (int errCode, ... ) {
    /* var length arg list function similar to printf() */
	char *s;
	float f;
	unsigned int i,j;
	size_t lenErrCode;
	va_list ap; /* argument pointer */
	va_start(ap,errCode); /* make ap point to first unnamed argument */
	lenErrCode=strlen(_ErrorMessage[errCode - 1]);
	for(j=0;j<lenErrCode;j++){
		if(_ErrorMessage[errCode - 1][j]!='%'){
			putchar(_ErrorMessage[errCode - 1][j]);
		} else {
			j++;
			if(_ErrorMessage[errCode - 1][j]=='d'){
				i=va_arg(ap,int);
				fprintf(stdin, "%d", i);
			} else if(_ErrorMessage[errCode - 1][j]=='f'){
				f=(float)va_arg(ap,double);
				fprintf(stdin, "%f", f);
			} else if(_ErrorMessage[errCode - 1][j]=='s'){
				s=va_arg(ap,char*);
				while(*s)
					putchar(*s++);
			} else 
				putchar(_ErrorMessage[errCode - 1][j]);
		}
			
	}
	putchar ('\n');
	abort ();
}

void longjmperror(void) {
	ThrowException (ex_code__);
}

void SignalHandler (int signal) {
	switch (signal) {
	case SIGHUP:
		THROW (SIGHUP_EXCEPTION);
		break;
	case SIGINT:
		THROW (SIGINT_EXCEPTION);
		break;
	case SIGILL:
		THROW (SIGILL_EXCEPTION);
		break;
	case SIGABRT:
		THROW (SIGABRT_EXCEPTION);
		break;
	case SIGFPE:
		THROW (SIGFPE_EXCEPTION);
		break;
	case SIGBUS:
		THROW (SIGBUS_EXCEPTION);
		break;
	case SIGSEGV:
		THROW (SIGSEGV_EXCEPTION);
		break;
	case SIGSYS:
		THROW (SIGSYS_EXCEPTION);
		break;
	case SIGTERM:
		THROW (SIGTERM_EXCEPTION);
		break;
	}
}

void longjmpsignalhandler (int signal) {
	if (signal == SIGSEGV) {
		longjmperror();
		printf ("Error: longjmp failed\n");
		abort();
	}
	printf ("Error: longjmp failed with code ");
	switch (signal) {
		case 1:
			printf ("SIGHUP\n");
			break;
		case 2:
			printf ("SIGINT\n");
			break;
		case 3:
			printf ("SIGQUIT\n");
			break;
		case 4:
			printf ("SIGILL\n");
			break;
		case 5:
			printf ("SIGTRAP\n");
			break;
		case 6:
			printf ("SIGABRT\n");
			break;
		case 7:
			printf ("SIGEMT\n");
			break;
		case 8:
			printf ("SIGFPE\n");
			break;
		case 9:
			printf ("SIGKILL\n");
			break;
		case 10:
			printf ("SIGBUS\n");
			break;
		case 11:
			printf ("SIGSEGV\n");
			break;
		case 12:
			printf ("SIGSYS\n");
			break;
		case 13:
			printf ("SIGPIPE\n");
			break;
		case 14:
			printf ("SIGALRM\n");
			break;
		case 15:
			printf ("SIGTERM\n");
			break;
		case 16:
			printf ("SIGURG\n");
			break;
		case 17:
			printf ("SIGSTOP\n");
			break;
		case 18:
			printf ("SIGTSTP\n");
			break;
		case 19:
			printf ("SIGCONT\n");
			break;
		case 20:
			printf ("SIGCHLD\n");
			break;
		case 21:
			printf ("SIGTTIN\n");
			break;
		case 22:
			printf ("SIGTTOU\n");
			break;
		case 23:
			printf ("SIGIO\n");
			break;
		case 24:
			printf ("SIGXCPU\n");
			break;
		case 25:
			printf ("SIGXFSZ\n");
			break;
		case 26:
			printf ("SIGVTALRM\n");
			break;
		case 27:
			printf ("SIGPROF\n");
			break;
		case 28:
			printf ("SIGWINCH\n");
			break;
		case 29:
			printf ("SIGINFO\n");
			break;
		case 30:
			printf ("SIGUSR1\n");
			break;
		case 31:
			printf ("SIGUSR2\n");
			break;
		default:
			printf ("UNKNOWN\n");
			break;
	}

	abort();
}

void longjmpthrow (jmp_buf state, int retvalue) {
	if (!was_try__) {
		longjmperror();
	}
	longjmp(state, retvalue);
}
