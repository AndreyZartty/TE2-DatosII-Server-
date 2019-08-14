#include <iostream>
#include "List.h"
#include "Node.h"


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <json-c/json.h>
#include <sstream>

#define PORT 3550
#define BACKLOG 4
#define MAXDATASIZE 1000

using namespace std;

static List* lista;



/**
 * Retorna al cliente el tamaño de la Zona de Intimidación.
 * @return JSON
 */

string sendRecibido() {


    json_object* jobjRecibido = json_object_new_object();

    json_object* jstringRecibido = json_object_new_string("Kenny Bell");

    json_object_object_add(jobjRecibido,"ZONESIZE", jstringRecibido);

    return json_object_to_json_string(jobjRecibido);

}

int runServer() {

    int fd, fd2;

    struct sockaddr_in server;

    struct sockaddr_in client;


    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("error en socket()\n");
        exit(-1);
    }

    server.sin_family = AF_INET;

    server.sin_port = htons(PORT);

    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server.sin_zero), 8);

    if (bind(fd, (struct sockaddr *) &server,
             sizeof(struct sockaddr)) == -1) {
        printf("error en bind() \n");
        exit(-1);
    }

    if (listen(fd, BACKLOG) == -1) {
        printf("error en listen()\n");
        exit(-1);
    }

    printf("\nServidor 'Gladiators - GBP' abierto.\n");

    while (true) {

        unsigned int address_size = sizeof(client);

        if ((fd2 = accept(fd, (struct sockaddr *) &client,
                          &address_size)) == -1) {
            printf("error en accept()\n");
            exit(-1);
        }

        printf("\nSe obtuvo una conexión de un cliente.\n");

        ssize_t r;

        char buff[MAXDATASIZE];

        for (;;) {
            r = read(fd2, buff, MAXDATASIZE);

            if (r == -1) {
                perror("read");
                return EXIT_FAILURE;
            }
            if (r == 0)
                break;
            printf("\nREAD: %s\n", buff);



            ///JSON Reads



            ///KEY: INSERT
            ///Obtiene el flag para comenzar el juego
            struct json_object* tempInsert;
            //cout<<"COMENZAR"<<endl;
            json_object* parsed_jsonInsert = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonInsert, "INSERT", &tempInsert);
            //printf("Por comenzar: %s\n", json_object_get_string(tempComenzar));






            ///KEYS HISTORIC LABELS



            /*
            ///KEY: TEMPLATE
            ///Obtiene un request para
            struct json_object *tempZZ;
            cout<<"ZZ"<<endl;
            json_object *parsed_jsonZZ = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonZZ, "ZZ", &tempZZ);
             */



            ///JSON Writes



            ///Obtendra un request para comenzar el juego
            ///Verifica que reciba los KEYS: INSERT
            if (json_object_get_string(tempInsert) != nullptr) {

                ///Conversion de string del cliente a int en el server
                stringstream temp(json_object_get_string(tempInsert));
                int insert;
                temp >> insert;

                ///Insertar al principio en la lista
                lista->insertFirst(insert);
                lista->getList();

                ///JSON saliente del servidor
                string Recibido = sendRecibido();
                ///Envio al cliente
                send(fd2, Recibido.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", Recibido.c_str());
            }



            /*
            ///Obtendra un request para obtener
            ///Verifica que reciba los KEYS: TEMPLATE
            if (json_object_get_string(tempZZ) != nullptr ) {
                ///JSON saliente del servidor
                string aTypeZZ = sendAType("ZZ",json_object_get_string(tempZZ));
                ///Envio al cliente
                send(fd2, aTypeZZ.c_str(), MAXDATASIZE, 0);
            }
             */

        }

        ///Reestablece el buffer
        memset(buff, 0, MAXDATASIZE);

        cout <<
             "\n\n--------------------------------------------------------------------------------"
             "END--------------------------------------------------------------------------------\n"
             << endl;

    }

    close(fd2);

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    List* prueba = new List();
    prueba->insertFirst(3);
    prueba->insertFirst(2);
    prueba->insertFirst(1);
    prueba->modifyNode(2,10);
    prueba->getList();
    cout << prueba->getNode(1) << endl;
    cout << "---------------" << endl;
    prueba->deleteFirst();
    prueba->getList();

    runServer();

}
