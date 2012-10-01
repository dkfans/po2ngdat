/*
 * poparser.h
 *
 *  Created on: 30-09-2012
 *      Author: tomasz
 */

#ifndef POPARSER_H_
#define POPARSER_H_

#include "message.h"
#include "str-list.h"

#define MAX_MESSAGE_SIZE 4096

enum {
    ERR_OK          =  0,
    ERR_CANT_OPEN   = -1, // fopen problem
    ERR_BAD_FILE    = -2, // incorrect file format
    ERR_NO_MEMORY   = -3, // malloc error
    ERR_FILE_READ   = -4, // fget/fread/fseek error
    ERR_FILE_WRITE  = -5, // fput/fwrite error
    ERR_LIMIT_EXCEED= -6, // static limit exceeded
    ERR_BAD_FORMAT  = -7, // input data format is invalid
};

typedef enum po_keyword po_keyword;
enum po_keyword {
  COMMENT,
  PREV_MSGCTXT,
  PREV_MSGID,
  PREV_MSGID_PLURAL,
  PREV_STRING,
  MSGCTXT,
  MSGID,
  MSGID_PLURAL,
  MSGSTR,
};

typedef struct pofile_catalog_reader_ty pofile_catalog_reader_ty;
struct pofile_catalog_reader_ty
{
    /** List of messages already appeared in the current file.  */
    msgdomain_list_ty *mdlp;

    /** Name of domain we are currently examining.  */
    const char *domain;

    /** List of messages belonging to the current domain.  */
    message_list_ty *mlp;

    /* Accumulate comments for next message directive.  */
    string_list_ty *comment_previd;
    string_list_ty *comment_del;

    /** Next message directive portions */
    message_ty nmsg;
    po_keyword kw;

};

FILE * open_catalog_file (const char *input_name);
pofile_catalog_reader_ty * pofile_catalog_reader_alloc(void);
void pofile_catalog_reader_free (pofile_catalog_reader_ty *pop);
short pofile_catalog_reader_parse(pofile_catalog_reader_ty *pop, FILE *fp, const char *logical_filename);

#endif /* POPARSER_H_ */
