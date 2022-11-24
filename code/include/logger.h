#ifndef SEETHE_H
#define SEETHE_H

#include <stdio.h>
#include <time.h>

/* Default level */
#ifndef LOG_LEVEL
    #define LOG_LEVEL   WARNING
#endif

/* Colour customization */
#define DEBUG_COLOUR    "\x1B[36m"
#define INFO_COLOUR     "\x1B[36m"
#define NOTICE_COLOUR   "\x1B[32;1m"
#define WARNING_COLOUR  "\x1B[33m"
#define ERROR_COLOUR    "\x1B[31m"
#define CRITICAL_COLOUR "\x1B[41;1m"

/* Do not change this. */
#define RESET_COLOUR    "\x1B[0m"

/* Formatting prefs. */
#define MSG_ENDING      "\n"
#define TIME_FORMAT     "%T"
#define BORDER          ""

/* Enabler flags */
#define DISPLAY_COLOUR  1
#define DISPLAY_TIME    1
#define DISPLAY_LEVEL   1
#define DISPLAY_FUNC    1
#define DISPLAY_FILE    1
#define DISPLAY_LINE    1
#define DISPLAY_BORDER  1
#define DISPLAY_MESSAGE 1
#define DISPLAY_ENDING  1
#define DISPLAY_RESET   1

#define LOG_DEBUG(Message) (debug(DEBUG_COLOUR,__FILE__, __func__, __LINE__, Message))
#define LOG_INFO(Message) (info(INFO_COLOUR,__FILE__, __func__, __LINE__, Message))
#define LOG_WARN(Message) (warning(WARNING_COLOUR,__FILE__, __func__, __LINE__, Message))
#define LOG_WARN(Message) (notice(NOTICE_COLOUR,__FILE__, __func__, __LINE__, Message))
#define LOG_ERROR(Message) (error(ERROR_COLOUR,__FILE__, __func__, __LINE__, Message))
#define LOG_CRITICAL(Message) (critical(CRITICAL_COLOUR,__FILE__, __func__, __LINE__, Message))

/* Log to screen */
void emit_log(char* colour,char* level,char* file,const char* func, int line,char* msg){
 do {                         
                                                                                    
    /* notate the time */                                                           
    time_t raw_time = time(NULL);                                                   
    char time_buffer[80];                                                           
    strftime(time_buffer, 80, TIME_FORMAT, localtime(&raw_time));                   
                                                                                    
    /* enable colour */                                                             
    printf("%s", DISPLAY_COLOUR ? colour : "");                                     
                                                                                    
    /* display the time */                                                          
    printf("%s%s | ", DISPLAY_TIME ? time_buffer : "", DISPLAY_TIME ? " " : "");    
                                                                                    
    /* display the level */                                                         
    printf("    %10s%s\t| ", DISPLAY_LEVEL ? level : "", DISPLAY_LEVEL ? " " : "");      
                                                                                    
    /* display the function doing the logging */                                    
    printf("%s%s\t| ", DISPLAY_FUNC ? func : "", DISPLAY_FUNC ? " " : "");           
                                                                                    
    /* display the file and/or the line number */                                   
    printf(                                                                         
        "%s%s%s%.d%s%s\t| ",                                                         
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? "(" : "",                  
        DISPLAY_FILE ? file : "",                                                   
        DISPLAY_FILE && DISPLAY_LINE ? ":" : "",                                    
        DISPLAY_LINE ? line : 0,                                                    
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? ") " : "",                 
        !DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? " " : ""                  
    );                                                                              
                                                                                    
    /* display message border */                                                    
    printf("%s%s", DISPLAY_BORDER ? BORDER : "", DISPLAY_BORDER ? " " : "");        
                                                                                    
    /* display the callee's message */                                              
    if (DISPLAY_MESSAGE) printf("%s",msg);                                       
                                                                                    
    /* add the message ending (usually '\n') */                                     
    printf("%s", DISPLAY_ENDING ? MSG_ENDING : "");                                 
                                                                                    
    /* reset the colour */                                                          
    printf("%s", DISPLAY_RESET ? RESET_COLOUR : "");
    
    FILE *fp;
    fp=fopen("../logs/log.txt","a");
    fprintf(fp,time_buffer);fprintf(fp," |   ");
    fprintf(fp,level);fprintf(fp,"\t| ");
    fprintf(fp,func);fprintf(fp,"\t| ");
    fprintf(fp,"(");fprintf(fp,file);fprintf(fp,":");
    fprintf(fp,"line: ");//fprintf(fp,line);ss
    fprintf(fp,")");fprintf(fp,"\t| ");
    fprintf(fp,msg);
    fprintf(fp,"\n");
    } while (0) ;                                                                                                                                                      
}
//fputs(time_buffer,file);

/* Level enum */
#define DEBUG       0
#define INFO        1
#define NOTICE      2
#define WARNING     3
#define ERROR       4
#define CRITICAL    5
#define SILENT      6

/* DEBUG LOG */
void debug(char* colour,char* file, const char* func, int line,char* msg){
do {                                                             
    if (LOG_LEVEL == DEBUG) {                                                       
        emit_log(DEBUG_COLOUR, "[DEBUG]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);
}
/* INFO LOG */
void info(char* colour,char* file, const char* func, int line,char* msg){ 
do {                                                              
    if (LOG_LEVEL <= INFO) {                                                        
        emit_log(INFO_COLOUR, "[INFO]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);
}

/* NOTICE LOG */
void notice(char* colour,char* file, const char* func, int line,char* msg){ do {                                                            
    if (LOG_LEVEL <= NOTICE) {                                                      
        emit_log(NOTICE_COLOUR, "[NOTICE]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);}

/* WARNING LOG */
void warning(char* colour,char* file, const char* func, int line,char* msg){ do {                                                           
    if (LOG_LEVEL <= WARNING) {                                                     
        emit_log(WARNING_COLOUR, "[WARNING]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);}

/* ERROR LOG */
void error(char* colour,char* file, const char* func, int line,char* msg){ do {                                                             
    if (LOG_LEVEL <= ERROR) {                                                       
        emit_log(ERROR_COLOUR, "[ERROR]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);}

/* CRITICAL LOG */
void critical(char* colour,char* file, const char* func, int line,char* msg){ do {                                                          
    if (LOG_LEVEL <= CRITICAL) {                                                    
        emit_log(CRITICAL_COLOUR, "[CRITICAL]", file, func, line, msg);                                                                          
    }                                                                               
} while (0);}

#endif // seethe.h
