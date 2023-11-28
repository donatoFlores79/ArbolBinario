#include <iostream>

using namespace std;

template <class T>
class Nodo{
public:
    T elem;
    Nodo<T>* izq;
    Nodo<T>* der;

    Nodo(T elemento) : elem(elemento), izq(nullptr), der(nullptr) {}
};

template <class T>
class Arbol{
private:
    Nodo<T>* raiz;
public:
    Arbol() : raiz(nullptr){}

    Nodo<T>* getRaiz() const;

    void inicializa();
    bool vacio() const;
    T recupera(Nodo<T>*);
    void inserta(T);
    void insertaRecursivo(Nodo<T>*&, T);
    Nodo<T>* localiza(T);
    Nodo<T>* localizaRecursivo(Nodo<T>*&, T);
    Nodo<T>* menor(Nodo<T>*) const;
    Nodo<T>* mayor(Nodo<T>*) const;
    bool esHoja(Nodo<T>*) const;
    void recorridoPreOrder(Nodo<T>*);
    void recorridoInOrder(Nodo<T>*);
    void recorridoPostOrder(Nodo<T>*);
    void elimina(Nodo<T>*);
    void eliminaRecursivo(Nodo<T>*, Nodo<T>*);
    int altura(Nodo<T>*) const;
    int factEq() const;
    void balanceo();
    void rotSimpDer();
    void rotSimpIzq();
    void rotDobDer();
    void rotDobIzq();
};

template <class T>
Nodo<T>* Arbol<T>::getRaiz() const{
    return raiz;
}

template <class T>
void Arbol<T>::inicializa(){
    raiz == nullptr;
}

template <class T>
bool Arbol<T>::vacio() const{
    return raiz == nullptr;
}

template <class T>
T Arbol<T>::recupera(Nodo<T>* pos){
    if(raiz == nullptr || pos == nullptr)
        cout<< "Insuficiencia de datos, recupera()";
    else
        return pos->elem;
}

template <class T>
void Arbol<T>::inserta(T elem){
    insertaRecursivo(raiz, elem);
}

template <class T>
void Arbol<T>::insertaRecursivo(Nodo<T>*& r, T elem){
    if(r == nullptr){
        Nodo<T>* aux = new Nodo<T>(elem);
        r = aux;
    }
    else if(elem < r->elem)
        insertaRecursivo(r->izq, elem);
    else
        insertaRecursivo(r->der, elem);
}

template <class T>
Nodo<T>* Arbol<T>::localiza(T elem){
    return localizaRecursivo(raiz, elem);
}

template <class T>
Nodo<T>* Arbol<T>::localizaRecursivo(Nodo<T>*& r, T elem){
    if(r == nullptr)
        return nullptr;
    else if(elem == r->elem)
        return r;
    else if(elem < r->elem)
        return localizaRecursivo(r->izq, elem);
    else
        return localizaRecursivo(r->der, elem);
}

template <class T>
Nodo<T>* Arbol<T>::menor(Nodo<T>* raiz) const{
    if(raiz == nullptr)
        return nullptr;
    else if(raiz->izq == nullptr)
        return raiz;
    else
        return menor(raiz->izq);
}

template <class T>
Nodo<T>* Arbol<T>::mayor(Nodo<T>* raiz) const{
    if(raiz == nullptr)
        return nullptr;
    else if(raiz->der == nullptr)
        return raiz;
    else
        return mayor(raiz->der);
}

template <class T>
bool Arbol<T>::esHoja(Nodo<T>* nodo) const{
    if(nodo == nullptr)
        return false;
    if(nodo->izq == nullptr && nodo->der == nullptr)
        return true;
    else
        return false;
}

template <class T>
void Arbol<T>::recorridoPreOrder(Nodo<T>* _raiz){
    if(_raiz == nullptr)
        return;

    cout<< _raiz->elem << "\n";
    recorridoPreOrder(_raiz->izq);
    recorridoPreOrder(_raiz->der);
}

template <class T>
void Arbol<T>::recorridoInOrder(Nodo<T>* _raiz){
    if(_raiz == nullptr)
        return;

    recorridoInOrder(_raiz->izq);
    cout<< _raiz->elem << "\n";
    recorridoInOrder(_raiz->der);
}

template <class T>
void Arbol<T>::recorridoPostOrder(Nodo<T>* _raiz){
    if(_raiz == nullptr)
        return;

    recorridoPostOrder(_raiz->izq);
    recorridoPostOrder(_raiz->der);
    cout<< _raiz->elem << "\n";
}

template <class T>
void Arbol<T>::elimina(Nodo<T>* pos){
    eliminaRecursivo(raiz, pos);
}
template <class T>
void Arbol<T>::eliminaRecursivo(Nodo<T>* raiz1, Nodo<T>* pos){
    if (raiz1 == nullptr || pos == nullptr) {
        cout << "Error, elimina()";
        return;
    }

    if (esHoja(raiz1)){
        delete raiz1;
        raiz1 = nullptr;
    }
    else{
        Nodo<T>* posReemplazo;

        if (raiz1->izq != nullptr)
            posReemplazo = mayor(raiz1->izq);
        else
            posReemplazo = menor(raiz1->der);

        raiz1->elem = posReemplazo->elem;
        eliminaRecursivo(raiz1, posReemplazo);
    }
}

template <class T>
int Arbol<T>::altura(Nodo<T>* raiz) const{
    if(raiz == nullptr)
        return 0;
    else{
        int alt_izq = altura(raiz->izq);
        int alt_der = altura(raiz->der);

        if(alt_izq > alt_der)
            return alt_izq + 1;
        else
            return alt_der + 1;
    }
}

template <class T>
int Arbol<T>::factEq() const{
    if(raiz == nullptr)
        return 0;
    else
        return altura(raiz->der) - altura(raiz->izq);
}

template <class T>
void Arbol<T>::balanceo(){
    if(factEq(raiz) < -1){
        if(factEq(raiz->izq) = -1)
            rotSimpDer(raiz);
        else
            rotDobDer(raiz);

        return;
    }

    if(factEq() > 1){
        if(factEq(raiz->izq) = 1)
            rotSimpIzq(raiz);
        else
            rotDobIzq(raiz);

        return;
    }

}

template <class T>
void Arbol<T>::rotSimpDer(){
    Nodo<T>* aux1 = raiz->izq;
    Nodo<T>* aux2 = raiz->izq->der;

    raiz->izq = aux2;
    aux1->der = raiz;
    raiz = aux1;
}

template <class T>
void Arbol<T>::rotSimpIzq(){
    Nodo<T>* aux1 = raiz->der;
    Nodo<T>* aux2 = raiz->der->izq;

    raiz->der = aux2;
    aux1->izq = raiz;
    raiz = aux1;
}

template <class T>
void Arbol<T>::rotDobDer(){
    Nodo<T>* aux1 = raiz->izq;
    Nodo<T>* aux2 = aux1->der;
    Nodo<T>* aux3 = aux2->izq;
    Nodo<T>* aux4 = aux2->der;

    raiz->izq = aux4;
    aux1->der = aux3;
    aux2->izq = aux1;
    raiz = aux2;
}

template <class T>
void Arbol<T>::rotDobIzq(){
    Nodo<T>* aux1 = raiz->der;
    Nodo<T>* aux2 = aux1->izq;
    Nodo<T>* aux3 = aux2->der;
    Nodo<T>* aux4 = aux2->izq;

    raiz->der = aux4;
    aux1->izq = aux3;
    aux2->der = aux1;
    raiz = aux2;
}

int main()
{
    Arbol<int> arbol;

    int opcion = 0;
    while(opcion != 8){
        cout<< "1.Insertar\n";
        cout<< "2.Buscar\n";
        cout<< "3.Menor\n";
        cout<< "4.Mayor\n";
        cout<< "5.Recorridos\n";
        cout<< "6.Elimina\n";
        cout<< "7.Altura\n";
        cout<< "8.Salir\n";
        cout<< " --->";
        cin>> opcion;

        switch(opcion){
        case 1:
        {
            int valor;
            cout<< "Valor a insertar:";
            cin>> valor;

            arbol.inserta(valor);

            cout<< "\n\n";

            break;
        }
        case 2:
        {
            int valor;
            cout<< "Valor a buscar:";
            cin>> valor;

            Nodo<int>* posEncontrada = arbol.localiza(valor);
            if(posEncontrada == nullptr)
                cout<< "No se encontro el valor\n";
            else{
                int valorEncontrado = arbol.recupera(posEncontrada);
                cout<< "Valor encontrado:" << valorEncontrado << "\n";
            }
            cout<< "\n\n";

            break;
        }
        case 3:
        {
            Nodo<int>* posMenor = arbol.menor(arbol.getRaiz());
            if(posMenor == nullptr)
                cout<< "Arbol vacio\n";
            else{
                int menor = arbol.recupera(posMenor);
                cout<< "Menor:" << menor << "\n";
            }
            cout<< "\n\n";

            break;
        }
        case 4:
        {
            Nodo<int>* posMayor = arbol.mayor(arbol.getRaiz());
            if(posMayor == nullptr)
                cout<< "Arbol vacio\n";
            else{
                int mayor = arbol.recupera(posMayor);
                cout<< "Mayor:" << mayor << "\n";
            }
            cout<< "\n\n";

            break;
        }
        case 5:
            cout<< "---  Recorrido pre-order  ---\n";
            arbol.recorridoPreOrder(arbol.getRaiz());
            cout<< "\n---  Recorrido in-order  ---\n";
            arbol.recorridoInOrder(arbol.getRaiz());
            cout<< "\n---  Recorrido post-order  ---\n";
            arbol.recorridoPostOrder(arbol.getRaiz());
            cout<< "\n\n";

            break;
        case 6:
        {
            int valor;
            cout<< "Valor a eliminar:";
            cin>> valor;

            Nodo<int>* posEncontrada = arbol.localiza(valor);
            if(posEncontrada == nullptr)
                cout<< "No se encontro el valor\n";
            else{
                int valorEncontrado = arbol.recupera(posEncontrada);
                arbol.elimina(posEncontrada);
                cout<< "Valor eliminado:" << valorEncontrado << "\n";
            }
            cout<< "\n\n";

            break;
        }
        case 7:
            cout<< "Altura:" << arbol.altura(arbol.getRaiz()) << "\n\n";
            break;
        case 8:
            break;
        default:
            cout<< "Ingresa una opcion valida\n";
        }
    }

    return 0;
}
