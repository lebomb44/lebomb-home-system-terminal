#ifndef _WEB_H_
#define _WEB_H_

#include <stdio.h>

__BEGIN_DECLS

extern int web_ASPCallback (char *pASPFunction, FILE *stream);

extern void fprintf_HTML_Head_Begin(FILE* stream);
extern void fprintf_HTML_Head_End(FILE* stream);
extern void fprintf_HTML_Title_Begin(FILE* stream);
extern void fprintf_HTML_Title_End(FILE* stream);
extern void fprintf_HTML_Body_Begin(FILE* stream);
extern void fprintf_HTML_Body_End(FILE* stream);
extern void fprintf_HTML_Redirection(prog_char* url_P, uint8_t delay, FILE* stream);
extern void fprintf_HTML_Page(prog_char* head_P, prog_char* title_P, prog_char* body_P, FILE* stream);
extern void fprintf_HTML_Page_Redirection(prog_char* url_P, uint8_t delay, prog_char* title_P, prog_char* body_P, FILE* stream);
extern void fprintf_HTML_Option(unsigned long int nb, unsigned long int comp, FILE *stream);
extern void fprintf_HTML_Option_and_String(unsigned long int nb, prog_char* str, unsigned long int comp, FILE *stream);
extern void fprintf_HTML_Option_List(unsigned long int begin, unsigned long int nb, unsigned int comp, FILE *stream);
extern void fprintf_XML_header(FILE *stream);
extern void fprintf_XML_elt_header(char* elt, FILE *stream);
extern void fprintf_XML_elt_trailer(char* elt, FILE *stream);
extern void fprintf_XML_elt_int(char* elt, int data, FILE *stream);
extern void fprintf_XML_elt_int02(char* elt, int data, FILE *stream);
extern void fprintf_XML_elt_str(char* elt, char* data, FILE *stream);

__END_DECLS

#endif
