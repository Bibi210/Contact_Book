#include <sqlite3.h>
#include <gtk/gtk.h>
#define CONTACT_SIZE ((guint8)9)

typedef GArray Contact_t;

void data_base_init(sqlite3 *db)
{
    gchar *errorsql = "Erreur sur la base de données";
    if (sqlite3_open("contacts_base.db", &db) != SQLITE_OK)
    {
        g_print("Impossible d'ouvrir la base de contacts");
        exit(-1);
    }

    if (sqlite3_exec(db, "SELECT * FROM contact_list;", 0, 0, &errorsql) != SQLITE_OK)
    {
        g_print("Creation de la table \n");
        sqlite3_exec(db, "CREATE TABLE contact_list (id INTEGER PRIMARY KEY AUTOINCREMENT,nom TEXT,prenom,TEXT,email TEXT,Adresse: TEXT,type TEXT,num1 TEXT,num2 TEXT,num3 TEXT,notes TEXT);", 0, 0, &errorsql);
        //* Exemple Pour insert value sqlite3_exec(db,"INSERT INTO contact_list (nom,prenom) VALUES('Brahima','Dibassi');",0,0,&errorsql);
    }
    sqlite3_exec(db, ".backup main  contacts_base.db;", 0, 0, &errorsql);
    sqlite3_close(db);
}   

void data_base_add_contact(Contact_t *un_type)
{
    //TODO sqlite3_bind_text(phrase en preparation ,Position du ?,Value a bind,Taille '-1',Callback);
}


int main()
{
    sqlite3 *db;
    data_base_init(db);

    gchar *test[CONTACT_SIZE];
    test[0] = "Dibassi";
    test[1] = "Brahima";
    test[2] = "brahimadibassi@gmail.com";
    test[3] = "20 rue sabran de ponteves";
    test[4] = "Pro";
    test[5] = "0615261588";
    test[6] = "";
    test[7] = "";
    test[8] = "Trop beau ce boug";

    g_print("%s \n", test[8]);


}
