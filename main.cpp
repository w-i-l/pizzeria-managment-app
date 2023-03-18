#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <Windows.h>

using namespace std;


// Ingredient
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Ingredient{
    private:

        char* nume;
        // glucide, lipide, proteine
        int* macronutrienti;
        bool de_post;
        // 0.ZZ/MM/YY
        float data_expirarii;
        // kg
        float cantitate;

    public:

        // getteri

        const char* get_nume() const{ return this->nume; }
        const int* get_macronutrienti() { return this->macronutrienti; }
        bool get_de_post() { return this->de_post; }
        float get_data_expirarii() { return this->data_expirarii; }
        float get_cantitate() { return this->cantitate; }

        // setteri

        void set_nume(const char* nume_nou){
            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];

            strcpy(this->nume, nume_nou);
        }

        void set_macronutrienti(int* macronutrienti_nou){
            if(this->macronutrienti == NULL){
                this->macronutrienti = new int[3];
            }

            for(int i=0; i<3; i++){
                this->macronutrienti[i] = macronutrienti_nou[i];
            }
        }

        void set_de_post(bool de_post_nou){ this->de_post = de_post_nou; }
        void set_data_expirarii(float data_expirarii_nou){ this->data_expirarii = data_expirarii_nou; }
        void set_cantitate(float cantitate_nou){ this->cantitate = cantitate_nou; }

        // contructori
        Ingredient();
        Ingredient(char* nume, int* macronutrienti, bool de_post, float data_expirarii, float cantitate);
        Ingredient(char* nume, int* macronutrienti);
        Ingredient(char* nume, float cantitate);
        Ingredient(const Ingredient &obj);

        // destructor
        ~Ingredient();

        // operatori
        Ingredient& operator=(const Ingredient& obj);
        int operator[](int);
        Ingredient& operator ++();
        Ingredient operator ++(int);
        Ingredient operator +(int);
        Ingredient operator -(int);
        Ingredient operator +(const Ingredient &obj);
        operator float()const; ///implicit
        bool operator == (const Ingredient &a);
        bool operator < (const Ingredient &a);

        
        // friend
        friend ostream& operator<<(ostream& out, const Ingredient& obj);
        friend istream& operator>>(istream& in, Ingredient& obj);
        friend Ingredient operator+(int a, const Ingredient&);
        friend Ingredient operator-(int a, const Ingredient&);

        // methods
        bool expirat();
        bool in_stoc();

    
};


Ingredient::Ingredient(){
    
    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = 0;
    
    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = 0.0;
}


Ingredient::Ingredient(char* nume, int* macronutrienti, bool de_post, float data_expirarii, float cantitate){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = macronutrienti[i];
    
    this->de_post = de_post;
    this->data_expirarii = data_expirarii;
    this->cantitate = cantitate;
}


Ingredient::Ingredient(char* nume, int* macronutrienti){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = macronutrienti[i];

    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = 0.0;
}


Ingredient::Ingredient(char* nume, float cantitate){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = 0;

    this->de_post = false;
    this->data_expirarii = 0.000000;
    this->cantitate = cantitate;
}


Ingredient::Ingredient(const Ingredient &obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->macronutrienti = new int[3];
    for(int i=0; i<3; i++)
        this->macronutrienti[i] = obj.macronutrienti[i];
    
    this->de_post = obj.de_post;
    this->data_expirarii = obj.data_expirarii;
    this->cantitate = obj.cantitate;
}


Ingredient::~Ingredient(){
    if(this->macronutrienti != NULL){
        delete[] this->macronutrienti;
        this->macronutrienti = NULL;
    }
    
    if(this->nume != NULL){
        delete[] this->nume;
        this->nume = NULL;
    }
}


Ingredient&  Ingredient::operator=(const Ingredient& obj){
    
    if(this != &obj){
        if(this->macronutrienti != NULL){
            delete[] this->macronutrienti;
            this->macronutrienti = NULL;
        }
        
        if(this->nume != NULL){
            delete[] this->nume;
            this->nume = NULL;
        }

        this->nume = new char[5];
        strcpy(this->nume, obj.nume);

        this->macronutrienti = new int[3];
        for(int i=0; i<3; i++)
            this->macronutrienti[i] = obj.macronutrienti[i];
        
        this->de_post = obj.de_post;
        this->data_expirarii = obj.data_expirarii;
        this->cantitate = obj.cantitate;
    }

    return *this;
}

// returns the nth macronutrient
int Ingredient::operator[](int a){

    if(this->macronutrienti == NULL) throw runtime_error("No ingredient!");
    if(a < 0 || a >=3 ) throw runtime_error("Invalid index!");
    
    return this->macronutrienti[a];

}


// increment by 1 the quantity
Ingredient& Ingredient::operator ++(){

    this->cantitate ++;
    return *this;

}


// increment by 1 the quantity
Ingredient Ingredient::operator ++(int){

    Ingredient coppy(*this);
    this->cantitate ++;
    return coppy;

}


// increment the quantity
Ingredient Ingredient::operator +(int a){

    Ingredient copy(*this);
    copy.cantitate += a;
    return copy;

}


// increment the quantity
Ingredient operator+(int a, const Ingredient& obj){

    Ingredient copy(obj);
    copy.cantitate += a;
    return copy;

}


// decrement the quantity
// throw a runtime_error if the result is negative
Ingredient Ingredient::operator -(int a){

    if(this->cantitate < a) {throw runtime_error("Not enough quantity!"); exit(-1);}

    Ingredient copy(*this);
    copy.cantitate -= a;
    return copy;

}


// decrement the quantity
// throw a runtime_error if the result is negative
Ingredient operator-(int a, const Ingredient& obj){

    if(obj.cantitate < a) {throw runtime_error("Not enough quantity!"); exit(-1);}

    Ingredient copy(obj);
    copy.cantitate -= a;
    return copy;

}


Ingredient Ingredient::operator +(const Ingredient &obj){

    Ingredient coppy(*this);

    coppy.cantitate += obj.cantitate;
    
    delete[] coppy.nume;
    coppy.nume = new char[strlen(this->nume) + strlen(obj.nume) + 2];
    strcpy(coppy.nume, this->nume);
    strcat(coppy.nume, "&");
    strcat(coppy.nume, obj.nume);

    for(int i=0; i<3; i++){
        coppy.macronutrienti[i] += obj.macronutrienti[i];
    }

    coppy.data_expirarii = min(this->data_expirarii, obj.data_expirarii);

    coppy.de_post = this->de_post && obj.de_post;

    return coppy;
}



// returns the quantity
Ingredient::operator float()const{

    return this->cantitate;

} ///implicit


// compares the names
bool Ingredient::operator == (const Ingredient &obj){

    bool nume = strcmp(this->nume, obj.nume);

    return nume == 0 ? true : false;

}


// compares the quantity
bool Ingredient::operator < (const Ingredient &obj){

    return this->cantitate < obj.cantitate;

}


ostream& operator<<(ostream& out, const Ingredient& obj){

    out << "   Detalii ingredient:" << endl;
    out << "     Nume: " << obj.nume << endl;
    out << "     Macronutrienti: " << obj.macronutrienti[0] << "g glucide " 
        << obj.macronutrienti[1] << "g lipide "
        << obj.macronutrienti[2] << "g proteine" << endl;
    out << "     De post: " << (obj.de_post ? "Da" : "Nu") << endl;
    out << "     Data expirarii: " << (int)(obj.data_expirarii * 100) << "."
        << (int)(obj.data_expirarii * 10000) % 100 << "."
        << 20 << (int)(obj.data_expirarii * 1000000) % 100 << endl;
    out << "     Cantitate: " << obj.cantitate << " kg" << endl;

    return out;
}


istream& operator>>(istream& in, Ingredient& obj){

    if(obj.macronutrienti != NULL){
        delete[] obj.macronutrienti;
        obj.macronutrienti = NULL;
    }
    
    if(obj.nume != NULL){
        delete[] obj.nume;
        obj.nume = NULL;
    }

    char aux[100];
    cout << "Citire detalii ingredient:" << endl;

    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Macronutrienti: ";
    obj.macronutrienti = new int[3];
    in >> obj.macronutrienti[0];
    // cout << " ";
    in >> obj.macronutrienti[1]; 
    // cout << " ";
    in >> obj.macronutrienti[2];
    cout << endl;

    cout << "De post (0/1): ";
    in >> obj.de_post;
    cout << endl;

    cout << "Data expirarii (0.DDMMYY): ";
    in >> obj.data_expirarii;
    cout << endl;

    cout << "Cantitate (0.aaaaaa): ";
    in >> obj.cantitate;
    cout << endl;

    return in;
}


// returneaza 1 daca a expirat
bool Ingredient::expirat(){
    time_t t = time(0);
    tm* now = localtime(&t);
    // formatam cum am salvat
    float current_date = (float)now->tm_mday /100 + (float)(now->tm_mon + 1)/10000 + (float)((now->tm_year + 1900) % 100) / 1000000;

    return current_date - this->data_expirarii > 0;
}

// returneaza 1 daca este in stoc
bool Ingredient::in_stoc(){
    return this->cantitate > 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Pizza
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Pizza{

    private:
        // diametru pizza in cm
        static int dimensiune_pizza;

        char* nume;
        int numar_ingrediente = 0;
        Ingredient* lista_ingrediente;
        float pret;
    
    public:

        // getteri
        static int get_dimensiune_pizza() { return Pizza::dimensiune_pizza; }
        const char* get_nume() const{ return this->nume; }
        int get_numar_ingrediente() { return this->numar_ingrediente; }
        const Ingredient* get_lista_ingrediente() { return this->lista_ingrediente; }
        float get_pret() {return this->pret; }

        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];

            strcpy(this->nume, nume_nou);
        }

        void set_lista_ingrediente(int numar_ingrediente_nou, const Ingredient* lista_ingrediente_nou){

            this->numar_ingrediente = numar_ingrediente_nou;

            if(this->lista_ingrediente != NULL){
                delete[] this->lista_ingrediente;
            }

            this->lista_ingrediente = new Ingredient[numar_ingrediente_nou];

            for(int i=0; i<numar_ingrediente_nou; i++){
                this->lista_ingrediente[i] = lista_ingrediente_nou[i];
            }
        }

        void set_pret(float pret_nou){
            this->pret = pret;
        }

        // constructori
        Pizza();
        Pizza(char* nume, int numar_ingrediente, Ingredient* lista_ingrediente, float pret);
        Pizza(char* nume, float pret);
        Pizza(char* nume);
        Pizza(const Pizza& obj);

        // destructor
        ~Pizza();

        // operatori
        Pizza& operator=(const Pizza& obj);
        Ingredient operator[](int);
        Pizza& operator ++();
        Pizza operator ++(int);
        Pizza operator +(const Ingredient&);
        Pizza operator -(const Ingredient&);
        Pizza operator +(const Pizza &obj);
        operator float()const; ///implicit
        bool operator == (const Pizza &obj);
        bool operator < (const Pizza &obj);

        // friend
        friend ostream& operator<<( ostream& out, const Pizza& obj);
        friend istream& operator>>( istream& in, Pizza& obj);
        friend Pizza operator+(Ingredient a, const Pizza& obj);
        friend Pizza operator-(Ingredient a, const Pizza& obj);

        // methods
        void afisare_valori_nutritionale() const;
        bool de_post();
        void afisare() const;
};      


int Pizza::dimensiune_pizza = 30;


Pizza::Pizza(void){

    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = 0;
}


Pizza::Pizza(char* nume, int numar_ingrediente, Ingredient* lista_ingrediente, float pret){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = numar_ingrediente;
    this->lista_ingrediente = new Ingredient[numar_ingrediente];
    for(int i=0; i<numar_ingrediente; i++)
        this->lista_ingrediente[i] = lista_ingrediente[i];

    this->pret = pret;
}


Pizza::Pizza(char* nume, float pret){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = pret;
}


Pizza::Pizza(char* nume){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_ingrediente = 0;
    this->lista_ingrediente = NULL;

    this->pret = 0; 
}


Pizza::Pizza(const Pizza& obj){
    
    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_ingrediente = obj.numar_ingrediente;
    this->lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->lista_ingrediente[i] = obj.lista_ingrediente[i];

    this->pret = obj.pret;
}


Pizza::~Pizza(){

    if(this->nume != NULL){
        delete this->nume;
    }

    if(this->lista_ingrediente != NULL){
        delete[] this->lista_ingrediente;
    }
}


Pizza& Pizza::operator=(const Pizza& obj){

    if(this->nume != NULL){
        delete this->nume;
    }

    if(this->lista_ingrediente != NULL){
        delete[] this->lista_ingrediente;
    }

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_ingrediente = obj.numar_ingrediente;
    this->lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->lista_ingrediente[i] = obj.lista_ingrediente[i];

    this->pret = obj.pret;

}


// returns the nth pizza
Ingredient Pizza::operator[](int a){

    if(this->lista_ingrediente == NULL) {throw runtime_error("No ingredient!"); exit(-1);}
    if(a < 0 || a >= this->numar_ingrediente) {throw runtime_error("Invalid index!"); exit(-1);}
    
    return this->lista_ingrediente[a];

}


// increases the price
Pizza& Pizza::operator ++(){

    this->pret ++;
    return *this;

}


// increases the price
Pizza Pizza::operator ++(int){

    Pizza coppy(*this);
    this->pret ++;
    return coppy;

}


// add a new ingredient
Pizza Pizza::operator +(const Ingredient& obj){

    Pizza coppy(*this);

    Ingredient* aux = new Ingredient[coppy.numar_ingrediente + 1];

    for(int i=0; i<coppy.numar_ingrediente; i++) aux[i] = coppy.lista_ingrediente[i];

    aux[coppy.numar_ingrediente++] = obj;

    delete[] coppy.lista_ingrediente;

    coppy.lista_ingrediente = aux; 

    return coppy;

}


// deletes the ingredient
// if not found throw a runtime error
Pizza Pizza::operator -(const Ingredient& obj){

    Pizza coppy(*this);

    for(int i=0; i<coppy.numar_ingrediente; i++){
        if(coppy.lista_ingrediente[i] == obj){
            coppy.lista_ingrediente[i] = coppy.lista_ingrediente[coppy.numar_ingrediente - 1];
            coppy.numar_ingrediente --;
            return coppy;
        }
    }

    throw runtime_error("The igredient wasn't found!");

}


// creates a new pizza concatenating
Pizza Pizza::operator +(const Pizza &obj){

    Pizza coppy(*this);

    char* nume = new char[strlen(coppy.nume) + strlen(obj.nume) + 4];
    strcpy(nume, this->nume);
    strcat(nume, " & ");
    strcat(nume, obj.nume);

    delete[] coppy.nume;
    coppy.nume = nume;

    coppy.pret += obj.pret;

    coppy.numar_ingrediente += obj.numar_ingrediente;
    Ingredient* aux = new Ingredient[coppy.numar_ingrediente];

    for(int i=0; i<this->numar_ingrediente; i++)
        aux[i] = this->lista_ingrediente[i];

    for(int i=0; i<obj.numar_ingrediente; i++){
        aux[i + this->numar_ingrediente] = obj.lista_ingrediente[i];
    }

    delete[] coppy.lista_ingrediente;
    coppy.lista_ingrediente = aux;
    cout << endl;
    return coppy;

}


// returns the price
Pizza::operator float()const{

    return this->pret;

} ///implicit


// compares all
bool Pizza::operator == (const Pizza &obj){

    if(strcmp(this->nume, obj.nume) == 0){
        if(this->pret == obj.pret){
            if(this->numar_ingrediente == obj.numar_ingrediente){
                return true;
            }
        }
    }

    return false;
}


// compares the price
bool Pizza::operator < (const Pizza &obj){
;
    return this->pret < obj.pret;

}


// adds a new ingredient
Pizza operator+(Ingredient a, const Pizza& obj){

    Pizza coppy(obj);

    Ingredient* aux = new Ingredient[obj.numar_ingrediente + 1];

    for(int i=0; i<coppy.numar_ingrediente; i++) aux[i] = coppy.lista_ingrediente[i];

    aux[coppy.numar_ingrediente++] = a;

    delete[] coppy.lista_ingrediente;

    coppy.lista_ingrediente = aux; 

    return coppy;

}


// deletes the ingredient
// if not found throw a runtime error
Pizza operator-(Ingredient a, const Pizza& obj){

    Pizza coppy(obj);

    for(int i=0; i<coppy.numar_ingrediente; i++){
        if(coppy.lista_ingrediente[i] == a){
            coppy.lista_ingrediente[i] = coppy.lista_ingrediente[coppy.numar_ingrediente - 1];
            coppy.numar_ingrediente --;
            return coppy;
        }
    }

    throw runtime_error("The igredient wasn't found!");

}


ostream& operator<<(ostream& out, const Pizza& obj){

    out << "  Informatii despre pizza: " << endl;
    out << "    Nume: " << obj.nume << endl;
    out << "    Lista ingrediente: " << endl;
    for(int i=0; i<obj.numar_ingrediente; i++)
        out << obj.lista_ingrediente[i];
    out << "    Pret: " << obj.pret << endl;
    out << endl;
    return out;
}


istream& operator>>(istream& in, Pizza& obj){

    if(obj.nume != NULL){
        delete obj.nume;
    }

    if(obj.lista_ingrediente != NULL){
        delete[] obj.lista_ingrediente;
    }

    char aux[100];
    cout << "Citire informatii: " << endl;

    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Numar ingrediente: ";
    in >> obj.numar_ingrediente;
    obj.lista_ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        in >> obj.lista_ingrediente[i];
    cout << endl;

    cout << "Pret: ";
    in >> obj.pret;
    cout << endl;

    return in;
}


void Pizza::afisare_valori_nutritionale() const{

    int macro[3] = {0};
    cout << "Total macronutrienti: " << endl;
    for(int i=0; i<this->numar_ingrediente; i++){
        const int* aux = this->lista_ingrediente[i].get_macronutrienti();
        // trecem prin macronutrieti
        for(int j=0; j<3; j++){
            macro[j] += aux[j];
        }
    }

    cout << macro[0] << "g glucide " 
        << macro[1] << "g lipide "
        << macro[2] << "g proteine" << endl;

}


bool Pizza::de_post(){
    for(int i=0; i<this->numar_ingrediente; i++){
        if(this->lista_ingrediente[i].get_de_post() == 0){
            return false;
        }
    }

    return true;
}


void Pizza::afisare() const{

    cout << this->nume<< " -- " << this->pret << "$"<< endl;

    for(int i=0; i<this->numar_ingrediente; i++)
        cout << this->lista_ingrediente[i].get_nume() << " ";

    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Angajat
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Angajat{
    
    private:

        char* nume;
        char sex;
        float salariu;
        char* nume_job;
        int numar_pizze_facute;
        Pizza* pizze_facute;

    public:

        // getteri
        const char* get_nume() { return this->nume; }
        char get_sex() { return this->sex; }
        float get_salariu() { return this->salariu; }
        const char* get_nume_job() { return this->nume_job; }
        int get_numar_pizze_facute() { return this->numar_pizze_facute; }
        const Pizza* get_pizze_facute() { return this->pizze_facute; };

        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL){
                delete[] this->nume;
            }

            this->nume = new char[strlen(nume_nou)+1];
            strcpy(this->nume, nume);
        }

        void set_sex(char sex_nou) {this->sex = sex_nou;}
        void set_salariu(float salariu_nou) { this->salariu = salariu_nou; }

        void set_nume_job(const char* nume_job_nou){

            if(this->nume_job != NULL){
                delete[] this->nume_job;
            }

            this->nume_job = new char[strlen(nume_job_nou)+1];
            strcpy(this->nume_job, nume_job_nou);
        }

        void adauga_pizza(Pizza pizza_noua){
            // nu avem nicio pizza facuta
            if(this->pizze_facute == NULL){
                this->pizze_facute = new Pizza[1];
                this->pizze_facute[0] = pizza_noua;
                this->numar_pizze_facute = 1;
                return;
            }

            Pizza* aux = new Pizza[this->numar_pizze_facute + 1];
            for(int i=0; i<this->numar_pizze_facute; i++){
                aux[i] = this->pizze_facute[i];
            }
            aux[this->numar_pizze_facute] = pizza_noua;
            this->numar_pizze_facute ++;

            delete[] this->pizze_facute;
            this->pizze_facute = aux;
        }

        void resetare_pizze_facute(){
            if(this->pizze_facute == NULL) return;

            delete[] this->pizze_facute;
            this->pizze_facute = NULL;
            this->pizze_facute = 0;
        }

        // constructori
        Angajat();
        Angajat(char* nume, char sex, float salariu, char* nume_job, int numar_pizze_facute, Pizza* pizze_facute);
        Angajat(char* nume, char sex);
        Angajat(char* nume, float salariu, char* nume_job);
        Angajat(const Angajat& obj);

        // destructor
        ~Angajat();

        // operatori
        Angajat& operator=(const Angajat& obj);
        Pizza operator[](int);
        Angajat& operator ++();
        Angajat operator ++(int);
        Angajat operator +(const Pizza&);
        Angajat operator -(const Pizza&);
        operator float()const; ///implicit
        bool operator == (const Angajat &obj);
        bool operator < (const Angajat &obj);

        // friend
        friend ostream& operator<<(ostream& out, const Angajat& obj);
        friend istream& operator>>(istream& in, Angajat& obj);
        friend Angajat operator+(Pizza a, const Angajat& obj);
        friend Angajat operator-(Pizza a, const Angajat& obj);

        // method
        int profit_facut();
        void afisare() const;

};


Angajat::Angajat(){
    
    this->nume = new char[5];
    strcpy(this->nume, "none");

    this->sex = 'x';
    this->salariu = 0;
    this->nume_job = new char[5];
    strcpy(this->nume_job, "none");
    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(char* nume, char sex, float salariu, char* nume_job, int numar_pizze_facute, Pizza* pizze_facute){
   
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = sex;
    this->salariu = salariu;

    this->nume_job = new char[strlen(nume_job)+1];
    strcpy(this->nume_job, nume_job);

    this->numar_pizze_facute = numar_pizze_facute;
    this->pizze_facute = new Pizza[numar_pizze_facute];
    for(int i=0; i<numar_pizze_facute; i++)
        this->pizze_facute[i] = pizze_facute[i];
}


Angajat::Angajat(char* nume, float salariu, char* nume_job){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = 'x';
    this->salariu = salariu;

    this->nume_job = new char[strlen(nume_job)+1];
    strcpy(this->nume_job, nume_job);

    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(char* nume, char sex){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->sex = sex;
    this->salariu = 0;
    
    this->nume_job = new char[5];
    strcpy(this->nume_job, "none");

    this->numar_pizze_facute = 0;
    this->pizze_facute = NULL;
}


Angajat::Angajat(const Angajat& obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->sex = obj.sex;
    this->salariu = obj.salariu;

    this->nume_job = new char[strlen(obj.nume_job)+1];
    strcpy(this->nume_job, obj.nume_job);

    this->numar_pizze_facute = obj.numar_pizze_facute;
    this->pizze_facute = new Pizza[obj.numar_pizze_facute];
    for(int i=0; i<obj.numar_pizze_facute; i++)
        this->pizze_facute[i] = obj.pizze_facute[i];
}


Angajat::~Angajat(){

    if(this->nume != NULL){
        delete[] this->nume;
    }

    if(this->nume_job != NULL){
        delete[] this->nume_job;
    }

    if(this->pizze_facute != NULL){
        delete[] this->pizze_facute;
    }
}


Angajat& Angajat::operator=(const Angajat& obj){

    if(this != &obj){

        if(this->nume != NULL){
            delete[] this->nume;
        }

        if(this->nume_job != NULL){
            delete[] this->nume_job;
        }

        if(this->pizze_facute != NULL){
            delete[] this->pizze_facute;
        }

        this->nume = new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);
        this->sex = obj.sex;
        this->salariu = obj.salariu;

        this->nume_job = new char[strlen(obj.nume_job)+1];
        strcpy(this->nume_job, obj.nume_job);

        this->numar_pizze_facute = obj.numar_pizze_facute;
        this->pizze_facute = new Pizza[obj.numar_pizze_facute];
        
        for(int i=0; i<obj.numar_pizze_facute; i++)
            this->pizze_facute[i] = obj.pizze_facute[i];
    }

    return *this;
}


// returns the nth pizza
Pizza Angajat::operator[](int a){

    if(this->pizze_facute == NULL) { throw runtime_error("No pizza!"); exit(-1);}
    if(a < 0 || a >= this->numar_pizze_facute) { throw runtime_error("Invalid index!"); exit(-1);}

    return this->pizze_facute[a];

}


// increases salary
Angajat& Angajat::operator ++(){

    this->salariu ++;
    return *this;

}


// increases salary
Angajat Angajat::operator ++(int){

    Angajat coppy(*this);
    this->salariu ++;
    return coppy;

}


// adds a new pizza
Angajat Angajat::operator +(const Pizza& obj){

    Angajat coppy(*this);

    Pizza* aux = new Pizza[coppy.numar_pizze_facute + 1];

    for(int i=0; i<coppy.numar_pizze_facute; i++)
        aux[i] = coppy.pizze_facute[i];
    
    aux[coppy.numar_pizze_facute++] = obj;

    delete[] coppy.pizze_facute;
    coppy.pizze_facute = aux;

    return coppy;

}


// deletes a pizza
// throw an error if not found
Angajat Angajat::operator -(const Pizza& obj){

    Angajat coppy(*this);

    for(int i=0; i<coppy.numar_pizze_facute; i++){
        if(coppy.pizze_facute[i] == obj){
            coppy.pizze_facute[i] = coppy.pizze_facute[coppy.numar_pizze_facute - 1];
            coppy.numar_pizze_facute --;
            return coppy;
        }
    }

    throw runtime_error("No pizza found!");
}


// returns salary
Angajat::operator float()const{

    return this->salariu;

} ///implicit


// compares names and salaries
bool Angajat::operator == (const Angajat &obj){

    bool nume = strcmp(this->nume, obj.nume);
    bool job  = strcmp(this->nume_job, obj.nume_job);

    return !nume && !job ? true : false;

}


// compares salary
bool Angajat::operator < (const Angajat &obj){

    return this->salariu < obj.salariu;

}


// adds a new pizza
Angajat operator+(Pizza a, const Angajat& obj){

    Angajat coppy(obj);

    Pizza* aux = new Pizza[coppy.numar_pizze_facute + 1];

    for(int i=0; i<coppy.numar_pizze_facute; i++)
        aux[i] = coppy.pizze_facute[i];

    aux[coppy.numar_pizze_facute++] = a;

    delete[] coppy.pizze_facute;
    coppy.pizze_facute = aux;

    return coppy;

}


// deletes a pizza
// throw an error if not found
Angajat operator-(Pizza a, const Angajat& obj){

    Angajat coppy(obj);

    for(int i=0; i<coppy.numar_pizze_facute; i++){
        if(coppy.pizze_facute[i] == a){
            coppy.pizze_facute[i] = coppy.pizze_facute[coppy.numar_pizze_facute - 1];
            coppy.numar_pizze_facute --;
            return coppy;
        }
    }

    throw runtime_error("No pizza found!");

}


ostream& operator<<(ostream& out, const Angajat& obj){

    out << "Detalii despre angajat: " << endl;
    out << "Nume: " << obj.nume << endl;
    out << "Sex: " << obj.sex << endl;
    out << "Salariu: " << obj.salariu << endl;
    out << "Job: " << obj.nume_job << endl;
    out << "Pizze facute: " << endl;
    for(int i=0; i<obj.numar_pizze_facute; i++)
        out << obj.pizze_facute[i];
    out << endl;

    return out;
}


istream& operator>>(istream& in, Angajat& obj){
    char aux[100];
    cout << "Introducere angajat: " << endl;
    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Sex: ";
    in >> obj.sex;
    cout << endl;

    cout << "Salariu: ";
    in >> obj.salariu;
    cout << endl;
    cout << "Job: ";
    in >> aux;
    obj.nume_job = new char[strlen(aux)+1];
    strcpy(obj.nume_job, aux);
    cout << endl;

    cout << "Numar pizze facute: ";
    in >> obj.numar_pizze_facute;
    for(int i=0; i<obj.numar_pizze_facute; i++)
        in >> obj.pizze_facute[i];
    cout << endl;

    return in;
}


int Angajat::profit_facut(){

    int aux = 0;

    for(int i=0; i<this->numar_pizze_facute; i++){
        aux += this->pizze_facute[i].get_pret();
    }

    return aux;

}


void Angajat::afisare()const{

    cout << this->nume << " sex:" << this->sex << endl;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 


// Pizzerie
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
class Pizzerie{

    private:
        
        char* nume;
        int numar_angajati;
        Angajat* angajati;
        int numar_ingrediente;
        Ingredient* ingrediente;
        float profit;
        Pizza* pizze;
        int numar_pizze;

    public:

        // getteri
        const char* get_nume() { return this->nume; }
        const int get_numar_angajati() { return this->numar_angajati; }
        const Angajat* get_angajati() { return this->angajati; }
        int get_numar_ingrediente() { return this->numar_ingrediente; }
        const Ingredient* get_ingrediente() { return this->ingrediente; }
        float get_profit() { return this->profit; }
        const Pizza* get_pizze() const{ return this->pizze; }
        int get_numar_pizze() { return this->numar_pizze; }


        // setteri
        void set_nume(const char* nume_nou){

            if(this->nume != NULL) delete[] this->nume;

            this->nume = new char[strlen(nume_nou)+1];
            strcpy(this->nume, nume_nou);
        }

        void adaugare_ingredient(const Ingredient& obj){
            // verificare daca exista si creste cantitate
            // daca nu adaugare
        }

        void stergere_ingredient(const Ingredient& obj){
            // daca exista il sterge
            // daca nu exista nu face nimic
        }

        void adaugare_angajat(const Angajat& obj){
            // verificare daca exista
            // daca nu, il adauga
        }

        void stergere_angajat(const Angajat& obj){
            // daca exista il sterge
            // daca nu exista nu face nimic
        }

        // constructori
        Pizzerie();
        Pizzerie(char* nume, int numar_angajati, Angajat* angajati, int numar_ingrediente, Ingredient* ingrediente, int numar_pizze, Pizza* pizze , float profit);
        Pizzerie(char* nume, int numar_angajati, int numar_ingrediente);
        Pizzerie(char* nume, float profit);
        Pizzerie(const Pizzerie& obj);

        // deconstructor
        ~Pizzerie();

        // operatori
        Pizzerie& operator=(const Pizzerie& obj);
        Angajat operator[](int);
        Pizzerie& operator ++();
        Pizzerie operator ++(int);
        Pizzerie operator +(const Angajat&);
        Pizzerie operator -(const Angajat&);
        Pizzerie operator +(const Pizza&);
        Pizzerie operator -(const Pizza&);
        operator float()const; ///implicit
        bool operator == (const Pizzerie &obj);
        bool operator < (const Pizzerie &obj);

        // friend
        friend ostream& operator<<(ostream& out, const Pizzerie& obj);
        friend istream& operator>>(istream& in, Pizzerie& obj);
        friend Pizzerie operator+(Angajat a, const Pizzerie& obj);
        friend Pizzerie operator-(Angajat a, const Pizzerie& obj);
        friend Pizzerie operator+(Pizza a, const Pizzerie& obj);
        friend Pizzerie operator-(Pizza a, const Pizzerie& obj);

        // methods
        void afisare_angajati_cu_jobu(const char* nume_job);
        void afisare_joburi();
        
        
};


Pizzerie::Pizzerie(){

    this->nume = new char[5];
    strcpy(this->nume, "none");
    this->numar_angajati = 0;
    this->angajati = NULL;
    this->numar_ingrediente = 0;
    this->ingrediente = NULL;
    this->numar_pizze = 0;
    this->pizze = NULL;
    this->profit = 0;
}


Pizzerie::Pizzerie(char* nume, int numar_angajati, Angajat* angajati, int numar_ingrediente, Ingredient* ingrediente, int numar_pizze, Pizza* pizze , float profit){
    
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = numar_angajati;
    this->angajati = new Angajat[numar_angajati];
    for(int i=0; i<numar_angajati; i++)
        this->angajati[i] = angajati[i];

    this->ingrediente = new Ingredient[numar_ingrediente];
    this->numar_ingrediente = numar_ingrediente;
    for(int i=0; i<numar_ingrediente; i++)
        this->ingrediente[i] = ingrediente[i];

    this->numar_pizze = numar_pizze;
    this->pizze = new Pizza[numar_pizze];
    for(int i=0; i<numar_pizze; i++)
        this->pizze[i] = pizze[i];

    this->profit = profit;
}


Pizzerie::Pizzerie(char* nume, int numar_angajati, int numar_ingrediente){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = numar_angajati;
    this->angajati = NULL;

    this->numar_ingrediente = numar_ingrediente;
    this->ingrediente = NULL;

    this->numar_pizze = 0;
    this->pizze = NULL;

    this->profit = 0;
}


Pizzerie::Pizzerie(char* nume, float profit){

    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);

    this->numar_angajati = 0;
    this->angajati = NULL;

    this->numar_ingrediente = 0;
    this->ingrediente = NULL;
    
    this->numar_pizze = 0;
    this->pizze = NULL;

    this->profit = profit;
}


Pizzerie::Pizzerie(const Pizzerie& obj){

    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_angajati = obj.numar_angajati;
    this->angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++)
        this->angajati[i] = obj.angajati[i];

    this->ingrediente = new Ingredient[obj.numar_ingrediente];
    this->numar_ingrediente = obj.numar_ingrediente;
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->ingrediente[i] = obj.ingrediente[i];

    this->numar_pizze = obj.numar_pizze;
    this->pizze = new Pizza[obj.numar_pizze];
    for(int i=0; i<obj.numar_pizze; i++)
        this->pizze[i] = obj.pizze[i];

    this->profit = obj.profit;
}


Pizzerie::~Pizzerie(){

    if(this->nume != NULL) delete[] this->nume;

    if(this->angajati != NULL) delete[] this->angajati;

    if(this->ingrediente != NULL) delete[] this->ingrediente;

    if(this->pizze != NULL) delete[] this->pizze;
}


Pizzerie& Pizzerie::operator=(const Pizzerie& obj){

    if(this == &obj) return *this;

    if(this->nume != NULL) delete[] this->nume;

    if(this->angajati != NULL) delete[] this->angajati;

    if(this->ingrediente != NULL) delete[] this->ingrediente;

    if(this->pizze != NULL) delete[] this->pizze;


    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);

    this->numar_angajati = obj.numar_angajati;
    this->angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++)
        this->angajati[i] = obj.angajati[i];

    this->numar_ingrediente = obj.numar_ingrediente;
    this->ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++)
        this->ingrediente[i] = obj.ingrediente[i];

    this->numar_pizze = obj.numar_pizze;
    this->pizze = new Pizza[obj.numar_pizze];
    for(int i=0; i<obj.numar_pizze; i++)
        this->pizze[i] = obj.pizze[i];

    this->profit = obj.profit;

    return *this;
}


// returns the nth employee +
Angajat Pizzerie::operator[](int a){

    if(this->angajati == NULL) { throw runtime_error("No employee!"); exit(-1);}
    if(a < 0 || a >= this->numar_angajati) { throw runtime_error("Invalid index!"); exit(-1);}

    return this->angajati[a];

}


// increases profit
Pizzerie& Pizzerie::operator ++(){

    this->profit ++;
    return *this;

}


// increases profit
Pizzerie Pizzerie::operator ++(int){

    Pizzerie coppy(*this);
    this->profit ++;
    return coppy;

}


// adds an employee
Pizzerie Pizzerie::operator +(const Angajat& obj){

    Pizzerie coppy(*this);

    Angajat* aux = new Angajat[coppy.numar_angajati + 1];

    for(int i=0; i<coppy.numar_angajati; i++)
        aux[i] = coppy.angajati[i];
    
    aux[coppy.numar_angajati ++ ] = obj;

    delete[] coppy.angajati;
    coppy.angajati = aux;

    return coppy;

}


// deletes an employee
// if not found throw an error
Pizzerie Pizzerie::operator -(const Angajat& obj){

    Pizzerie coppy(*this);

    for(int i=0; i<coppy.numar_angajati; i++){
        if(coppy.angajati[i] == obj){
            coppy.angajati[i] = coppy.angajati[coppy.numar_angajati - 1];
            coppy.numar_angajati --;
            return coppy;
        }
    }

    throw runtime_error("No employee!");

}


// adds an Pizza
Pizzerie Pizzerie::operator +(const Pizza& obj){

    Pizzerie coppy(*this);

    Pizza* aux = new Pizza[coppy.numar_pizze + 1];

    for(int i=0; i<coppy.numar_pizze; i++)
        aux[i] = coppy.pizze[i];
    
    aux[coppy.numar_pizze ++ ] = obj;

    delete[] coppy.pizze;
    coppy.pizze = aux;

    return coppy;

}


// deletes an Pizza
// if not found throw an error
Pizzerie Pizzerie::operator -(const Pizza& obj){

    Pizzerie coppy(*this);

    for(int i=0; i<coppy.numar_pizze; i++){
        if(coppy.pizze[i] == obj){
            coppy.pizze[i] = coppy.pizze[coppy.numar_pizze - 1];
            coppy.numar_pizze --;
            return coppy;
        }
    }

    throw runtime_error("No Pizza!");

}


// returns profit
Pizzerie::operator float()const{

    return this->profit;

} ///implicit


// compares names
bool Pizzerie::operator == (const Pizzerie &obj){

    bool result = strcmp(this->nume, obj.nume);
    return result == 0 ? true : false;

}


// compares profits
bool Pizzerie::operator < (const Pizzerie &obj){

    return this->profit < obj.profit;

}


// adds an employee
Pizzerie operator+(Angajat a, const Pizzerie& obj){


    Pizzerie coppy(obj);

    Angajat* aux = new Angajat[coppy.numar_angajati + 1];

    for(int i=0; i<coppy.numar_angajati; i++)
        aux[i] = coppy.angajati[i];
    
    aux[coppy.numar_angajati ++ ] = a;

    delete[] coppy.angajati;
    coppy.angajati = aux;

    return coppy;

}


// deletes an employee
// if not found throw an error
Pizzerie operator-(Angajat a, const Pizzerie& obj){

    Pizzerie coppy(obj);

    for(int i=0; i<coppy.numar_angajati; i++){
        if(coppy.angajati[i] == a){
            coppy.angajati[i] = coppy.angajati[coppy.numar_angajati - 1];
            coppy.numar_angajati --;
            return coppy;
        }
    }

    throw runtime_error("No employee!");

}


// adds an pizza
Pizzerie operator+(Pizza a, const Pizzerie& obj){


    Pizzerie coppy(obj);

    Pizza* aux = new Pizza[coppy.numar_pizze + 1];

    for(int i=0; i<coppy.numar_pizze; i++)
        aux[i] = coppy.pizze[i];
    
    aux[coppy.numar_pizze ++ ] = a;

    delete[] coppy.pizze;
    coppy.pizze = aux;

    return coppy;

}


// deletes an pizza
// if not found throw an error
Pizzerie operator-(Pizza a, const Pizzerie& obj){

    Pizzerie coppy(obj);

    for(int i=0; i<coppy.numar_pizze; i++){
        if(coppy.pizze[i] == a){
            coppy.pizze[i] = coppy.pizze[coppy.numar_pizze - 1];
            coppy.numar_pizze --;
            return coppy;
        }
    }

    throw runtime_error("No Pizza!");

}


ostream& operator<<(ostream& out, const Pizzerie& obj){
    
    out << "Informatii despre Pizzerie: " << endl;
    out << "Nume: " << obj.nume << endl;

    out << "Angajati: " << endl;
    for(int i=0; i<obj.numar_angajati; i++){
        out << obj.angajati[i];
    }

    out << "Profit: " << obj.profit << endl;
}


istream& operator>>(istream& in, Pizzerie& obj){

    char aux[100];

    cout << "Citire Pizzerie: " << endl;
    cout << "Nume: ";
    in >> aux;
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);
    cout << endl;

    cout << "Numar angajati: ";
    in >> obj.numar_angajati;
    obj.angajati = new Angajat[obj.numar_angajati];
    for(int i=0; i<obj.numar_angajati; i++){
        in >> obj.angajati[i];
    }
    cout << endl;

    cout << "Numar ingrediente: ";
    in >> obj.numar_ingrediente;
    obj.ingrediente = new Ingredient[obj.numar_ingrediente];
    for(int i=0; i<obj.numar_ingrediente; i++){
        in >> obj.ingrediente[i];
    }
    cout << endl;

    cout << "Profit: ";
    in >> obj.profit;
    cout << endl;
}


void Pizzerie::afisare_angajati_cu_jobu(const char* nume_job){
    for(int i=0; i<this->numar_angajati; i++){
        if(strcmp(this->angajati[i].get_nume_job(), nume_job) == 0)
            cout << this->angajati[i] << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Pizzerie init(){

    int valori[3];
    Ingredient branza, sunca, oua, ketchup, mozzarella, carnati, ananas, ardei, porumb, masline, pui, rosie;
    Pizza salami, casei, hawai, mic_dejun, vegana, taraneasca;
    Angajat maria, ion, gica, andrei;
    Pizza pizze[20];
    int nr_pizze;

    valori[0] = 10; valori[1] = 27; valori[2] = 40;
     branza = Ingredient("Branza", valori, false, 0.121224, 3);

    valori[0] = 5; valori[1] = 7; valori[2] = 10;
     sunca = Ingredient("Sunca", valori, false, 0.130923, 100);

    valori[0] = 2; valori[1] = 4; valori[2] = 7;
     oua = Ingredient("Oua", valori, false, 0.201023, 50);
    
    valori[0] = 12; valori[1] = 4; valori[2] = 9;
     ketchup = Ingredient("Ketchup", valori, true, 0.011025, 10);
    
    valori[0] = 1; valori[1] = 1; valori[2] = 1;
     mozzarella = Ingredient("Mozzarella", valori, false, 0.021123, 25);

    valori[0] = 30; valori[1] = 40; valori[2] = 31;
     carnati = Ingredient("Carnati", valori, false, 0.120324, 30);

    valori[0] = 11; valori[1] = 11; valori[2] = 11;
     ananas = Ingredient("Ananas", valori, true, 0.121029, 10);

    valori[0] = 43; valori[1] = 12; valori[2] = 31;
     ardei = Ingredient("Ardei", valori, true, 0.041124, 42);

    valori[0] = 7; valori[1] = 41; valori[2] = 21;
     porumb = Ingredient("Porumb", valori, true, 0.220125, 15);

    valori[0] = 19; valori[1] = 21; valori[2] = 13;
     rosie = Ingredient("Rosie", valori, true, 0.311024, 40);

    valori[0] = 21; valori[1] = 51; valori[2] = 21;
     masline = Ingredient("Masline", valori, true, 0.300525, 100);
    
    valori[0] = 51; valori[1] = 21; valori[2] = 11;
     pui = Ingredient("Pui", valori, true, 0.100225, 20);
    
    Ingredient ingrediente[10] = {mozzarella, ketchup, carnati, rosie, ardei, sunca};
     salami = Pizza("Salami", 6, ingrediente, 32.5);

    ingrediente[2] = ananas;
    ingrediente[3] = porumb;
    ingrediente[4] = pui;
     hawai = Pizza("Hawai", 5, ingrediente, 40);

    ingrediente[2] = ardei;
    ingrediente[3] = porumb;
    ingrediente[4] = masline;
    ingrediente[5] = sunca;
     taraneasca = Pizza("Taraneasca", 6, ingrediente, 25);

    ingrediente[2] = branza;
    ingrediente[3] = oua;
    ingrediente[4] = pui;
    ingrediente[5] = sunca;
     mic_dejun = Pizza("Mic-Dejun", 6, ingrediente, 35);

    ingrediente[0] = ardei;
    ingrediente[2] = porumb;
    ingrediente[3] = masline;
    ingrediente[4] = rosie;
     vegana = Pizza("Vegana", 5, ingrediente, 27.5);

    ingrediente[2] = branza;
    ingrediente[3] = oua;
    ingrediente[4] = pui;
    ingrediente[5] = rosie;
    ingrediente[6] = carnati;
    ingrediente[7] = porumb;
    ingrediente[8] = pui;
    casei = Pizza("Casei", 9, ingrediente, 50);
    
    pizze[0] = salami;
    pizze[1] = vegana;
    pizze[2] = mic_dejun;
    pizze[3] = taraneasca;
    pizze[4] = hawai;
    pizze[5] = casei;
    nr_pizze = 6;

    andrei = Angajat("Andrei", 'm', 1500,"ospatar", 0, NULL);
    ion = Angajat("Ion", 'm', 5500,"manager", 0, NULL);
    gica = Angajat("Gica", 'm', 2500,"ospatar", 0, NULL);
    maria = Angajat("Maria", 'f', 4500,"bucatar", 0, NULL);

    Angajat angajati[] = {andrei, ion, maria, gica};
    Ingredient ing[] = {branza, sunca, oua, ketchup, mozzarella, carnati, ananas, ardei, porumb, masline, pui, rosie};
    
    return Pizzerie("Maestro", 4, angajati, 12, ing, 6, pizze ,1000);
}


void manager(Pizzerie maestro){

    int option;
    Angajat aux;
    Pizza pizza;
    char nume[40];

    while(true){
        cout << "\n\tManager Menu" << endl;
        cout << "1. View profit" << endl;
        cout << "2. View employees" << endl;
        cout << "3. Fire employee" << endl;
        cout << "4. Hire employee" << endl;
        cout << "5. Search by job" << endl;
        cout << "6. Delete a pizza" << endl;
        cout << "7. Add pizza" << endl;
        cout << "Press q to exit." << endl;
        cout << "Please choose an option: ";

        cin >> option;
        system("cls");

        switch(option){

            case 1:
                cout <<"Profitul pizzeriei: "<<maestro.get_profit() << endl;
                break;

            case 2:
                for(int i=0; i<maestro.get_numar_angajati(); i++)
                    maestro.get_angajati()[i].afisare();
                    break;

            case 3:

                if(maestro.get_numar_angajati() == 0){
                    cout << "No employees!" << endl;
                    break;
                }

                for(int i=0; i<maestro.get_numar_angajati(); i++){
                    cout << i << " ";
                    maestro.get_angajati()[i].afisare();
                }

                int nr;

                cout << "Choose an employee to fire: ";
                cin >> nr;

                if(nr < 0 || nr >= maestro.get_numar_angajati()){
                    cout << "Enter a valid number!" << endl;
                    break;
                }

                maestro = maestro - maestro.get_angajati()[nr];

                cout << "Fired!" << endl;
                break;

            case 4:
                
                cin >> aux;

                maestro = maestro + aux;

                cout << "Added!" << endl;
                break;

            case 5:
                
                cout << "Enter job: ";
                cin >> nume;
                nume[strlen(nume)]=0;
                cout << endl;

                maestro.afisare_angajati_cu_jobu(nume);

            case 6:

                for(int i=0; i<maestro.get_numar_pizze(); i++)
                    cout << i << " " << maestro.get_pizze()[i].get_nume() << endl;

                cout << "Select pizza: ";
                cin >> option;

                if(option < 0 || option >= maestro.get_numar_pizze()) throw runtime_error("Invalid Index");

                maestro = maestro - maestro.get_pizze()[option];
                cout << "Deleted" << endl;
                break;
            
            case 7:

                cin >> pizza;

                maestro = maestro + pizza;
                cout << "Added";
                break;

            case 0:
                exit(0);

            default:
            cout << "Enter a valid option!" << endl;
            break;
        }
    }
}


void client(Pizzerie maestro){


    int option;
    

    while(true){

        cout << "\n\t Menu" << endl;
        cout << "1. Menu" << endl;
        cout << "2. Info ingredient" << endl;
        cout << "3. Macros pizza" << endl;
        cout << "4. Order pizza" << endl;
        cout << "Press q to exit" << endl;

        cin >> option;
        system("cls");

        switch(option){

            case 1:

                for(int i=0; i<maestro.get_numar_pizze(); i++)
                    maestro.get_pizze()[i].afisare();
                
                cout << endl;
                break;

            case 2:

                for(int i=0; i<maestro.get_numar_ingrediente(); i++){
                    cout << i << " " << maestro.get_ingrediente()[i].get_nume() << endl;
                }

                cout << "Choose an ingredient: ";
                cin >> option;
                cout << endl;

                cout << maestro.get_ingrediente()[option] << endl;
                break;

            case 3:
                for(int i=0; i<maestro.get_numar_pizze(); i++){
                    cout << i << " " << maestro.get_pizze()[i].get_nume() << endl;
                }

                cout << "Choose an ingredient: ";
                cin >> option;
                cout << endl;

                maestro.get_pizze()[option].afisare_valori_nutritionale();
                cout << endl;
                break;

            case 4:
                for(int i=0; i<maestro.get_numar_pizze(); i++){
                    cout << i << " " << maestro.get_pizze()[i].get_nume() << endl;
                }   

                cout << "Choose a pizza: ";
                cin >> option;
                cout << endl;

                Sleep(1000);
                cout << "Preparing..." << endl;
                
                Sleep(1000);
                cout << "Baking..." << endl;
                
                Sleep(2000);
                cout << "Ready to be served!" << endl;

                cout << "Done" << endl;
                break;

            case 0:
                exit(0);

            default:
            cout << "Enter a valid option!" << endl;
            break;
        }
    }
}


void menu(Pizzerie maestro){
    int option;

    while(true){    
        cout << "\tMenu" << endl;
        cout << "1. Client" << endl;
        cout << "2. Manager" << endl;
        cout << "Press q to exit." << endl;
        cout << "Please choose an option: ";
        cin >> option;

        system("cls");

        switch(option){
            case 1:
                client(maestro);
                break;

            case 2:
                manager(maestro);
                break;

            case 0:
                exit(0);

            default:
            cout << "Enter a valid option!" << endl;
            break;
        }
    }
}


int main(){

    Pizzerie maestro;

    maestro = init();
    menu(maestro);

    return 0;
}
