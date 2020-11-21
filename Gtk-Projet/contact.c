#include "contact.h"

void global_list_init()
{
    //TODO Prendre les contacts depuis un fichier
    _Contact_list = g_hash_table_new(g_str_hash, g_str_equal);
}

void init_contact(GList *contact_data)
{
    Contact_t *Untype = NULL;
    gint Nb_num = 0;
    //TODO Modifier
    Untype->Name = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Untype->Name);

    Untype->Prenom = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Untype->Prenom);

    Untype->Email = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Untype->Email);

    Nb_num = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Nb_num);

    for (gint i = 0; i < Nb_num; i++)
    {
        Untype->Numero = g_list_append(Untype->Numero, g_strdup(g_list_first(contact_data)->data));
        contact_data = g_list_remove(contact_data, g_list_first(contact_data)->data);
    }

    Untype->Anniv = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Untype->Anniv);

    Untype->Adresse = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, Untype->Adresse);

    g_hash_table_insert(_Contact_list, Untype->Name, Untype);
    _Current_Contact = Untype;
}

void modify_contact(GList *contact_data)
{
    gchar* Nb_num_char;
    gint Nb_num = 0;
    //TODO Modifier
    _Current_Contact->Name = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, _Current_Contact->Name);

    _Current_Contact->Prenom = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, _Current_Contact->Prenom);

    _Current_Contact->Email = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, _Current_Contact->Email);

    Nb_num_char = g_strdup(g_list_first(contact_data)->data);

    Nb_num = 

    contact_data = g_list_remove(contact_data, Nb_num);

    for (gint i = 0; i < Nb_num; i++)
    {
        _Current_Contact->Numero = g_list_append(_Current_Contact->Numero, g_strdup(g_list_first(contact_data)->data));
        contact_data = g_list_remove(contact_data, g_list_first(contact_data)->data);
    }

    _Current_Contact->Anniv = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, _Current_Contact->Anniv);

    _Current_Contact->Adresse = g_strdup(g_list_first(contact_data)->data);
    contact_data = g_list_remove(contact_data, _Current_Contact->Adresse);

    g_hash_table_insert(_Contact_list, _Current_Contact->Name, _Current_Contact);
}

void lookup_Contact(gchar *name)
{
    _Current_Contact = g_hash_table_lookup(_Contact_list, name);
}

void del_contact()
{
    g_hash_table_remove(_Contact_list, _Current_Contact->Name);
    g_free(_Current_Contact->Name);
    g_free(_Current_Contact->Prenom);
    g_free(_Current_Contact->Email);
    g_free(_Current_Contact->Adresse);
    g_free(_Current_Contact->Anniv);
    g_slist_free(_Current_Contact->Numero);
    _Current_Contact = NULL;
}

GList *list_contact_sorted()
{
    GList *Contact_list_to_print = NULL;
    Contact_t *to_add = NULL;
    gchar *str_to_add;

    for (GList *encours = g_hash_table_get_values(_Contact_list);
         encours != NULL;
         encours = encours->next)
    {
        to_add = encours->data;
        str_to_add = g_strjoin(" ", to_add->Name, to_add->Prenom);
        Contact_list_to_print = g_list_insert_sorted(Contact_list_to_print, str_to_add, (GCompareFunc)g_strcmp0);
    }
    return Contact_list_to_print;
}

int main()
{
    return 0;
}