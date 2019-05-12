#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *url_params, char *token, char *cookie1, char *cookie2)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    
    /*
        PAS 1: Scriem numele metodei, calea, parametri din url (daca exista) si tipul protocolului
    */

    if (url_params != NULL)
    {
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else
    {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    /*
        PAS 2: Adaugam host-ul
    */

    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    /*
        PAS 3 (optional): Adaugam headere si/ sau cookies, respectand forma protocolului
    */

    memset(line, 0, LINELEN);
    sprintf(line, "Authorization: Basic %s", token);
    compute_message(message, line);
    // TODO BONUS COOKIE
    memset(line, 0, LINELEN);
    sprintf(line, "Cookie: %s", cookie1);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Cookie: %s", cookie2);
    compute_message(message, line);

    /*
        PAS 4: Adaugam linia de final
    */

    strcat(message, "\r\n");
    return message;
}
char *compute_post_request(char *host, char *url, char *form_data,char *type, char *cookie1, char *cookie2)
{

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    /*
        PAS 1: Scriem numele metodei, calea si tipul protocolului
    */

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    /*
        PAS 2: Adaugam host-ul
    */

    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    /*
        PAS 3: Adaugam headere si/ sau cookies, respectand forma protocolului
        ATENTIE!! Headerele Content-Type si Content-Length sunt obligatorii
    */

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Type: %s", type);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Cookie: %s", cookie1);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Cookie: %s", cookie2);
    compute_message(message, line);

    /*
        PAS 4: Adaugam linia de final de antent
    */

    strcat(message, "\r\n");

    /*
        PAS 5: Adaugam data
    */

    //strcat(message, form_data);
    compute_message(message, form_data);
    return message;
}
