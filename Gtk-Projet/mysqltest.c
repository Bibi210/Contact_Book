#include <sqlite3.h>
#include <gtk/gtk.h>
#define CONTACT_SIZE ((guint8)10)

sqlite3 *_db;

void data_base_init()
{
    gchar *errorsql = "Erreur sur la base de données";
    if (sqlite3_open("contacts_base.db", &_db) != SQLITE_OK)
    {
        g_print("Impossible d'ouvrir la base de contacts");
        exit(-1);
    }

    if (sqlite3_exec(_db, "SELECT * FROM contact_list;", 0, 0, &errorsql) != SQLITE_OK)
    {
        g_print("Creation de la table \n");
        sqlite3_exec(_db, "CREATE TABLE contact_list (id TEXT,nom TEXT,prenom,TEXT,email TEXT,adresse TEXT,type TEXT,num1 TEXT,num2 TEXT,num3 TEXT,notes TEXT);", 0, 0, &errorsql);
        //* Exemple Pour insert value sqlite3_exec(db,"INSERT INTO contact_list (nom,prenom) VALUES('Brahima','Dibassi');",0,0,&errorsql);
    }
    sqlite3_exec(_db, ".backup main  contacts_base.db;", 0, 0, &errorsql);
}

void data_base_add_contact(GList *un_type)
{
    gint i = 1;
    sqlite3_stmt *commande;
    sqlite3_prepare_v2(_db, "INSERT INTO contact_list (id,nom,prenom,email,adresse,type,num1,num2,num3,notes) VALUES(?,?,?,?,?,?,?,?,?,?);", -1, &commande, NULL);

    for (GList *encours = un_type; encours != NULL; encours = encours->next)
    {
        sqlite3_bind_text(commande, i, encours->data, -1, NULL);
        i++;
    }
    sqlite3_step(commande);
    sqlite3_finalize(commande);
}

void data_base_del_contact(gchar* id){
    sqlite3_stmt *commande;
    sqlite3_prepare_v2(_db, "DELETE FROM contact_list WHERE id = ?;", -1, &commande, NULL);
    sqlite3_bind_text(commande,1,id,-1,NULL);
    sqlite3_step(commande);
    sqlite3_finalize(commande);
}

void data_base_modify_contact(GList *contact_data){
    data_base_del_contact(contact_data->data);
    data_base_add_contact(contact_data);
}

int print_data_callback(void *useless, gint argc, gchar **argv,gchar **azColName){
    
    for (gint i=0;i < argc;i++){
        g_print("%s = %s\n",azColName[i],argv[i]? argv[i]:"...."); 
    }
    (void) useless;
    return 0;
}
void data_base_print(){
    sqlite3_exec(_db,"SELECT * FROM contact_list ORDER BY nom",print_data_callback,0,NULL);
}



void data_base_lookup(gchar* recherche){
    //TODO ajouter d'autre option de recherche
   sqlite3_stmt *commande;
   sqlite3_prepare_v2(_db,"SELECT * FROM contact_list WHERE prenom = ? OR nom = ? OR num1 = ? OR num2 = ? OR num3 = ?",-1,&commande,NULL);
   for (gint i = 0; i <= 5; i++){
   sqlite3_bind_text(commande,i,recherche,-1,NULL);
   }
   while (sqlite3_step(commande) == SQLITE_ROW) 
   {
       g_print("%s\n",sqlite3_column_text(commande,1));
   }
   
   
}

int main()
{
    data_base_init();

    GList *test_contact = NULL;
    test_contact = g_list_append(test_contact, "1");
    test_contact = g_list_append(test_contact, "Dibassi");
    test_contact = g_list_append(test_contact, "Brahima");
    test_contact = g_list_append(test_contact, "brahimadibassi@gmail.com");
    test_contact = g_list_append(test_contact, "20 rue sabran de ponteves");
    test_contact = g_list_append(test_contact, "Pro");
    test_contact = g_list_append(test_contact, "0615261588");
    test_contact = g_list_append(test_contact, "");
    test_contact = g_list_append(test_contact, "");
    test_contact = g_list_append(test_contact, "Trop beau ce boug");

    GList *bibi = NULL;
    bibi = g_list_append(bibi, "6");
    bibi = g_list_append(bibi, "Zidane");
    bibi = g_list_append(bibi, "Brahima");
    data_base_add_contact(bibi);
    data_base_add_contact(test_contact);
    
    data_base_lookup("0615261588");


    //! gcc -fanalyzer -Wall -Wextra mysqltest.c -o  mysqltest -g `pkg-config --cflags --libs gtk+-3.0` -lsqlite3  && mysqltest
    //* qlite3_bind_text(phrase en preparation ,Position du ?,Value a bind,Taille '-1',Callback);
    //* select * from contact_list WHERE id = '2'
    data_base_del_contact("1");
    data_base_del_contact("6");
    sqlite3_close(_db);
}
