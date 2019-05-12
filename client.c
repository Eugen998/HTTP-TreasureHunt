#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "cJSON.c"
#include "cJSON.h"

int main(int argc, char *argv[])
{
    int sockfd;
    char rasp1[BUFLEN];
    char enunt2[BUFLEN];

    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    send_to_server(sockfd, compute_get_request("185.118.200.35", "/task1/start", NULL, NULL, NULL, NULL));

    strcpy(rasp1, receive_from_server(sockfd));
    strcpy(enunt2, strchr(rasp1,'{'));

    close_connection(sockfd);

    //parsam headerul http pt a extrage cookie urile
    char *cookies = strstr(rasp1,"Set-Cookie: ");
    char *cookie1 = strchr(cookies,' ');
    char *cookie2 = strchr(strstr(cookie1,"Set-Cookie"),' ');
    cookie1 = strtok(cookie1,";");
    cookie2 = strtok(cookie2,";");

    const cJSON *url2 = NULL;
    const cJSON *method2 = NULL;
    const cJSON *type2 = NULL;
    const cJSON *data2 = NULL;
    const cJSON *username2 = NULL;
    const cJSON *pass2 = NULL;

    //parsam continutul JSON al raspunsului de la server
    cJSON *task2 = cJSON_Parse(enunt2);
    url2 = cJSON_GetObjectItemCaseSensitive(task2, "url");
    method2 = cJSON_GetObjectItemCaseSensitive(task2, "method");
    type2 = cJSON_GetObjectItemCaseSensitive(task2, "type");
    data2 = cJSON_GetObjectItemCaseSensitive(task2, "data");
    username2 = cJSON_GetObjectItemCaseSensitive(data2, "username");
    pass2 = cJSON_GetObjectItemCaseSensitive(data2, "password");

    char rasp2[BUFLEN];
    char enunt3[BUFLEN];
    char form_data2[LINELEN];
    char *post2;

    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    sprintf(form_data2,"username=%s&password=%s",username2->valuestring, pass2->valuestring);
    post2 = compute_post_request("185.118.200.35",url2->valuestring, form_data2, type2->valuestring, cookie1, cookie2);

    send_to_server(sockfd, post2);
    strcpy(rasp2, receive_from_server(sockfd));
    strcpy(enunt3,strchr(rasp2,'{'));

    close_connection(sockfd);

    memset(cookie1, 0, LINELEN);
    memset(cookie2, 0, LINELEN);

    cookies = strstr(rasp2,"Set-Cookie: ");
    cookie1 = strchr(cookies,' ');
    cookie2 = strchr(strstr(cookie1,"Set-Cookie"),' ');
    cookie1 = strtok(cookie1,";");
    cookie2 = strtok(cookie2,";");


    const cJSON *url3 = NULL;
    const cJSON *method3 = NULL;
    const cJSON *data3 = NULL;
    const cJSON *token3 = NULL;
    const cJSON *query_params3 = NULL;
    const cJSON *id3 = NULL;

    cJSON *task3 = cJSON_Parse(enunt3);
    url3 = cJSON_GetObjectItemCaseSensitive(task3, "url");
    method3 = cJSON_GetObjectItemCaseSensitive(task3, "method");
    data3 = cJSON_GetObjectItemCaseSensitive(task3, "data");
    token3 = cJSON_GetObjectItemCaseSensitive(data3,"token");
    query_params3 = cJSON_GetObjectItemCaseSensitive(data3, "queryParams");
    id3 = cJSON_GetObjectItemCaseSensitive(query_params3,"id");


    char params3[LINELEN],line[LINELEN];
    sprintf(params3,"raspuns1=Omul&raspuns2=Numele&id=%s",id3->valuestring);

    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);

    send_to_server(sockfd, compute_get_request("185.118.200.35", url3->valuestring, params3, token3->valuestring, cookie1, cookie2));
    char rasp3[BUFLEN];
    char enunt4[BUFLEN];
    strcpy(rasp3, receive_from_server(sockfd));
    close_connection(sockfd);

    strcpy(enunt4, strchr(rasp3,'{'));

    cookies = strstr(rasp3,"Set-Cookie: ");
    cookie1 = strchr(cookies,' ');
    cookie2 = strchr(strstr(cookie1,"Set-Cookie"),' ');
    cookie1 = strtok(cookie1,";");
    cookie2 = strtok(cookie2,";");

    const cJSON *url4 = NULL;
    const cJSON *method4 = NULL;

    cJSON *task4 = cJSON_Parse(enunt4);
    url4 = cJSON_GetObjectItemCaseSensitive(task4, "url");
    method4 = cJSON_GetObjectItemCaseSensitive(task4, "method");

    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    send_to_server(sockfd, compute_get_request("185.118.200.35", url4->valuestring, NULL, token3->valuestring, cookie1, cookie2));
    char rasp4[BUFLEN];
    char enunt5[BUFLEN];
    strcpy(rasp4, receive_from_server(sockfd));
    close_connection(sockfd);

    strcpy(enunt5, strchr(rasp4,'{'));
    printf("%s",enunt5);

    cookies = strstr(rasp4,"Set-Cookie: ");
    cookie1 = strchr(cookies,' ');
    cookie2 = strchr(strstr(cookie1,"Set-Cookie"),' ');
    cookie1 = strtok(cookie1,";");
    cookie2 = strtok(cookie2,";");

    const cJSON *url5post = NULL;
    const cJSON *type5  = NULL;
    const cJSON *url5get = NULL;
    const cJSON *method5post = NULL;
    const cJSON *method5get = NULL;
    const cJSON *data5 = NULL;
    const cJSON *query_params5 = NULL;
    const cJSON *q = NULL;
    const cJSON *appid = NULL;

    cJSON *task5 = cJSON_Parse(enunt5);
    url5post = cJSON_GetObjectItemCaseSensitive(task5, "url");
    method5post = cJSON_GetObjectItemCaseSensitive(task5, "method");
    type5 = cJSON_GetObjectItemCaseSensitive(task5, "type");
    data5 = cJSON_GetObjectItemCaseSensitive(task5, "data");
    url5get = cJSON_GetObjectItemCaseSensitive(data5,"url");
    query_params5 = cJSON_GetObjectItemCaseSensitive(data5,"queryParams");
    q = cJSON_GetObjectItemCaseSensitive(query_params5, "q");
    appid = cJSON_GetObjectItemCaseSensitive(query_params5, "APPID");

    char params5[LINELEN];
    sprintf(params5, "q=%s&APPID=%s",q->valuestring,appid->valuestring);



    return 0;
}
