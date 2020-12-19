#include "../header/data_base.h"

//! { DIBASSI Brahima} 19005521 \\\\  
//! { KANOUTE Daouda} 19000407}  \\
//! \date {Dimanche 20 Décembre 2020}

extern void data_base_init()
{
    gchar *errorsql = "Erreur sur la base de données";
    if (sqlite3_open("contacts_base.db", &_db) != SQLITE_OK)
    {
        g_print("Impossible d'ouvrir la base de contacts");
        exit(-1);
    }

    if (sqlite3_exec(_db, "SELECT * FROM contact_list;", 0, 0, &errorsql) != SQLITE_OK)
    {
        sqlite3_exec(_db, "CREATE TABLE contact_list (nom TEXT,prenom TEXT,email TEXT,adresse TEXT,CP TEXT,type TEXT,num1 TEXT,num2 TEXT,num3 TEXT);", 0, 0, &errorsql);
    }
    sqlite3_exec(_db, ".backup main  contacts_base.db;", 0, 0, &errorsql);
}

void data_base_close()
{
    sqlite3_close(_db);
}

extern void data_base_add_contact(GList *un_type)
{
    gint i = 1;
    sqlite3_stmt *commande;
    sqlite3_prepare_v2(_db, "INSERT INTO contact_list (nom,prenom,email,adresse,CP,type,num1,num2,num3) VALUES(?,?,?,?,?,?,?,?,?);", -1, &commande, NULL);

    for (GList *encours = un_type; encours != NULL; encours = encours->next)
    {
        sqlite3_bind_text(commande, i, encours->data, -1, NULL);
        i++;
    }
    sqlite3_step(commande);
    sqlite3_finalize(commande);
}

extern void data_base_del_contact(gchar *id)
{
    sqlite3_stmt *commande;
    sqlite3_prepare_v2(_db, "DELETE FROM contact_list WHERE id = ?;", -1, &commande, NULL);
    sqlite3_bind_text(commande, 1, id, -1, NULL);
    sqlite3_step(commande);
    sqlite3_finalize(commande);
}

extern void data_base_modify_contact(GList *contact_data)
{
    data_base_del_contact(contact_data->data);
    data_base_add_contact(contact_data);
}

extern GList *data_base_lookup(gchar *recherche)
{
    GList *Contacts = NULL;
    GList *Untype = NULL;
    sqlite3_stmt *commande;
    sqlite3_prepare_v2(_db, "SELECT * FROM contact_list WHERE prenom = ? OR nom = ? OR num1 = ? OR num2 = ? OR num3 = ? OR id = ?", -1, &commande, NULL);
    for (gint i = 0; i <= 5; i++)
    {
        sqlite3_bind_text(commande, i, recherche, -1, NULL);
    }
    while (sqlite3_step(commande) == SQLITE_ROW)
    {
        Untype = NULL;
        for (gint t = 0; t < CONTACT_SIZE; t++)
        {
            gchar *bref = g_strdup((gchar *)sqlite3_column_text(commande, t));
            Untype = g_list_append(Untype, bref);
        }
        Contacts = g_list_append(Contacts, Untype);
    }
    for (GList *encours = Contacts; encours != NULL; encours = encours->next)
    {
        for (GList *To_print = encours->data; To_print != NULL; To_print = To_print->next)
        {
            g_print("%s\n", (gchar *)To_print->data);
        }
        g_print("\n");
    }
    sqlite3_finalize(commande);
    return Contacts;
}

extern GList *data_base_retrive(void)
{
    sqlite3_stmt *commande;
    GList *Untype = NULL;
    GList *Contacts = NULL;
    sqlite3_prepare_v2(_db, "SELECT * FROM contact_list ORDER BY nom", -1, &commande, NULL);
    while (sqlite3_step(commande) == SQLITE_ROW)
    {
        Untype = NULL;
        for (gint i = 0; i < CONTACT_SIZE; i++)
        {
            gchar *bref = g_strdup((gchar *)sqlite3_column_text(commande, i));
            Untype = g_list_append(Untype, bref);
        }
        Contacts = g_list_append(Contacts, Untype);
    }
    sqlite3_finalize(commande);
    return Contacts;
}

extern void data_base_clear(void)
{
    sqlite3_exec(_db, "DELETE FROM contact_list;", 0, 0, NULL);
}

extern int print_data_callback(void *useless, gint argc, gchar **argv, gchar **azColName)
{

    for (gint i = 0; i < argc; i++)
    {
        g_print("%s = %s\n", azColName[i], argv[i] ? argv[i] : "....");
    }
    (void)useless;
    return 0;
}
extern void data_base_print()
{
    sqlite3_exec(_db, "SELECT * FROM contact_list ORDER BY nom", print_data_callback, 0, NULL);
}
