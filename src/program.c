#include<stdio.h>
#include<util.h>
#include<argp.h>
#include<string.h>
#include<stdlib.h>

#define NUMARGS 0

const char * argp_program_version = "0.0.0.0.1";
const char * argp_program_bug_address = "info@internet.com";



//struct used in parse_opt further down to take the state
struct arguments
{
    char *args[NUMARGS];            /* ARG1 and ARG2 */
    int verbose;              /* The -v flag */
    char *outfile;            /* Argument for -o */
    char *stringa, *stringb, *stringc;  /* Arguments for -a and -b */
};


//argp field 1: Options
static struct argp_option options[] =
{
    //NAME, KEY, ARG, FLAGS, DOC
    {"verbose", 'v',0 ,0, "Give a verboserer output.",0 },
    {"alpha", 'a', "STRINGA", 0, "do something with STRINGA and a",0},
    {"bravo",   'b', "STRINGB", 0,
   "Do something with STRINGB related to the letter B",0},
   {"charlie",   'c', "STRINGC", 0,
   "Do something with STRINGC related to the letter C",0},
    {"output",  'o', "OUTFILE", 0,
   "Output to OUTFILE instead of to standard output",0},
    {0} // always ends with a {0}  for some reason?
};

//argp field 2: the parser
error_t parser (int key, char *arg, struct argp_state *state)
{
    //make an arguments struct with state->input pointer
    struct arguments *arguments = state->input;

    //switch over the key
    switch (key)
    {
    case 'v':
        arguments->verbose = 1;
        break;
    case 'a':
        arguments->stringa = arg;
        break;
    case 'b':
        arguments->stringb = arg;
        break;
    case 'c':
        arguments->stringc = arg;
        break;
    case 'o':
        arguments->outfile = arg;
        break;
    case ARGP_KEY_ARG:
    // too many args
        if(state->arg_num >= NUMARGS)
        {
            argp_usage(state);
        }
        arguments->args[state->arg_num] = arg;
        break;
    case ARGP_KEY_END:
        //not enough args
        if(state->arg_num < NUMARGS)
        {
            argp_usage(state);
        }
        break;
    
    default:
        return ARGP_ERR_UNKNOWN;
    }
return 0;
}

//3 ARGS_DOCS char args_doc[]

//4 program dopcumentation also a char []


//this is the actual argp struct that needs filling and passing to argp_parse in main
static struct argp argp =
{
    /* this data: https://www.gnu.org/software/libc/manual/html_node/Argp-Parsers.html */
    options,
    parser,
    "ARGA, ARGB, ARGC",
    "This is the program documentation you are welcome.",
    0,
    0,
    0
};


int main(int argc, char **argv) 
{
    struct arguments arguments;
    FILE *outstream;

    char something[] = "This is a something which is for verbose mayhbe?\n";

    arguments.outfile = NULL;
    arguments.stringa = "";
    arguments.stringb = "";
    arguments.stringc = "";
    arguments.verbose = 0;

    // This is the magic bit. 
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    //where the output goes
    if (arguments.outfile)  
        outstream = fopen (arguments.outfile, "w");
    else
        outstream = stdout;
    
    //print argument values
    fprintf (outstream, "alpha = %s\nbravo = %s\ncharlie = %s\n\n", 
                arguments.stringa, arguments.stringb, arguments.stringc);
    fprintf(outstream, "ARGA = %s\nARGB = %s\nARGC = %s\n\n",
            arguments.args[0],
            arguments.args[1],
            arguments.args[2]);

    if (arguments.verbose)
        fprintf(outstream, "%s",something);

    if(strcmp(arguments.stringa, "+") == 0)
    {
        printf("The sum of %d and %d is %d \n\n", 
        atoi(arguments.stringb), 
        atoi(arguments.stringc), 
        adder(atoi(arguments.stringb),atoi(arguments.stringc)));
    }
   
    return 0;
}