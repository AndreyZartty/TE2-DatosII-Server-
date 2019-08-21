#include <iostream>
#include "List.h"
#include "Node.h"

#include <arpa/inet.h>

#include <chrono>

#include <thread>
#include <string>


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

    string msm = "Se ha insertado a la lista correctamente";

    json_object* jstringRecibido = json_object_new_string(msm.c_str());

    json_object_object_add(jobjRecibido,"RECIBIDO_L", jstringRecibido);

    return json_object_to_json_string(jobjRecibido);

}

string sendModificado() {


    json_object* jobjModificado = json_object_new_object();

    string msm = "Se ha modificado la lista correctamente";

    json_object* jstringModificado = json_object_new_string(msm.c_str());

    json_object_object_add(jobjModificado,"MODIFICADO_L", jstringModificado);

    return json_object_to_json_string(jobjModificado);

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

    printf("\nServidor 'TE DATOS II' abierto.\n");

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



            ///KEY: INSERT_LIST
            ///Obtiene un request para insertar a la lista
            struct json_object* tempInsertL;
            json_object* parsed_jsonInsertL = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonInsertL, "INSERT_LIST", &tempInsertL);

            ///KEY: DELETE_LIST
            ///Obtiene un request para borrar el primero de la lista
            struct json_object *tempDeleteL;
            json_object *parsed_jsonDeleteL = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonDeleteL, "DELETE_LIST", &tempDeleteL);

            ///KEY: EDIT_LIST
            ///Obtiene un request para editar una posicion de la lista
            struct json_object *tempEditL;
            json_object *parsed_jsonEditL = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonEditL, "EDIT_LIST", &tempEditL);

            ///KEY: POS_TO_EDIT
            ///Obtiene la posicion a editar
            struct json_object *tempPosEditL;
            json_object *parsed_jsonPosEditL = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPosEditL, "POS_TO_EDIT", &tempPosEditL);

            ///KEY: GET_FROM_LIST
            ///Obtiene un request para obtener de la lista
            struct json_object *tempGetFromL;
            json_object *parsed_jsonGetFromL = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonGetFromL, "GET_FROM_LIST", &tempGetFromL);





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
            ///Verifica que reciba los KEYS: INSERT_LIST
            if (json_object_get_string(tempInsertL) != nullptr) {
                

                ///Conversion de string del cliente a int en el server
                stringstream temp(json_object_get_string(tempInsertL));

                int insert;
                temp >> insert;

                ///Insertar al principio en la lista
                
                lista->insertFirst(insert);

                cout << "\nLista:" << endl;
                lista->getList();

                ///JSON saliente del servidor
                string Recibido = sendRecibido();

                ///Envio al cliente
                send(fd2, Recibido.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", Recibido.c_str());
            }

            if (json_object_get_string(tempEditL) != nullptr) {


                ///Conversion de string del cliente a int en el server
                stringstream temp(json_object_get_string(tempEditL));

                int dataEdit;
                temp >> dataEdit;


                if (json_object_get_string(tempPosEditL) != nullptr){

                    stringstream temp(json_object_get_string(tempPosEditL));

                    int posEdit;
                    temp >> posEdit;

                    ///Modificar la lista

                    lista->modifyNode(posEdit,dataEdit);

                    cout << "\nLista:" << endl;
                    lista->getList();

                    ///JSON saliente del servidor
                    string Modificado = sendModificado();

                    ///Envio al cliente
                    send(fd2, Modificado.c_str(), MAXDATASIZE, 0);
                    printf("\nWRITE: %s\n", Modificado.c_str());

                }

            }

            if (json_object_get_string(tempGetFromL) != nullptr) {


                ///Conversion de string del cliente a int en el server
                stringstream temp(json_object_get_string(tempGetFromL));

                int getFromL;
                temp >> getFromL;

                json_object* jobjGetFromL = json_object_new_object();

                string msm = to_string(lista->getNode(getFromL));

                json_object* jstringGetFromL = json_object_new_string(msm.c_str());

                json_object_object_add(jobjGetFromL,"GET_P_L", jstringGetFromL);



                cout << "\nLista:" << endl;
                lista->getList();

                ///JSON saliente del servidor
                string GetFromL = json_object_to_json_string(jobjGetFromL);

                ///Envio al cliente
                send(fd2, GetFromL.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", GetFromL.c_str());
            }

            if (json_object_get_string(tempDeleteL) != nullptr) {

                lista->deleteFirst();

                json_object* jobjDeleteL = json_object_new_object();

                string msm = "Se ha eliminado el primer objeto de la lista";

                json_object* jstringDeleteL = json_object_new_string(msm.c_str());

                json_object_object_add(jobjDeleteL,"ELIMINADO_L", jstringDeleteL);



                cout << "\nLista:" << endl;
                lista->getList();

                ///JSON saliente del servidor
                string DeleteL = json_object_to_json_string(jobjDeleteL);

                ///Envio al cliente
                send(fd2, DeleteL.c_str(), MAXDATASIZE, 0);
                printf("\nWRITE: %s\n", DeleteL.c_str());
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
    std::cout << "Prueba" << std::endl;
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
    
    lista = new List();
    runServer();

}
