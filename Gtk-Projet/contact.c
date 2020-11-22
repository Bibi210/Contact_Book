#include "contact.h"

void global_list_init(gchar *filename)
{
    //TODO Prendre les contacts depuis un fichier
    _Contact_list = g_hash_table_new(g_str_hash, g_str_equal);
    (void)filename;
}

void search_keys(){
    GHashTable* key_gen = g_hash_table_new(g_str_hash, g_str_equal);
    GList* key_list = g_hash_table_get_keys(_Contact_list);
    Contact_t* To_process;

    for (GList* encours = key_list;encours != NULL;encours = encours->next){
       To_process = g_hash_table_lookup(_Contact_list,encours->data);
       for (GList* i = all_search_field_of_contact(To_process);i != NULL;i = i->next){
           g_hash_table_insert(key_list,i->data,encours->data);
       }
    }
}
GList* all_search_field_of_contact(Contact_t* Untype){
    GList* Sortie = NULL;
    Sortie = g_list_append(Sortie,Untype->Name);
    Sortie = g_list_append(Sortie,Untype->Prenom);
    Sortie = g_list_append(Sortie,Untype->Email);
    for (GList* encours = Untype->Numero;encours != NULL; encours = encours ->next)
    {
       Sortie = g_list_append(Sortie,encours->data);
    }
    return Sortie;
    
}


void init_contact(GList *contact_data)
{
    Contact_t *Untype = g_try_malloc(sizeof(Contact_t));
    gint Nb_num = 0;
    gchar *Nb_num_char;

    Untype->Name = g_try_malloc(sizeof(gchar));
    Untype->Prenom = g_try_malloc(sizeof(gchar));
    Untype->Email = g_try_malloc(sizeof(gchar));
    Untype->Anniv = g_try_malloc(sizeof(gchar));
    Untype->Adresse = g_try_malloc(sizeof(gchar));
    Untype->Notes = g_try_malloc(sizeof(gchar));
    Untype->Numero = g_try_malloc(sizeof(GList));

    Untype->Name = NULL;
    Untype->Prenom = NULL;
    Untype->Email = NULL;
    Untype->Adresse = NULL;
    Untype->Notes = NULL;
    Untype->Numero = NULL;
    Untype->Anniv = NULL;

    Untype->Name = g_strdup(contact_data->data);
    assert(Untype->Name);
    contact_data = contact_data->next;
    
    Untype->Prenom = g_strdup(contact_data->data);
    assert(Untype->Prenom);
    contact_data = contact_data->next;

    Untype->Email = g_strdup(contact_data->data);
    assert(Untype->Email);
    contact_data = contact_data->next;

    Nb_num_char = g_strdup(contact_data->data);
    assert(Nb_num_char);

    Nb_num = g_ascii_strtoll(Nb_num_char, NULL, 10);

    contact_data = contact_data->next;
    for (gint i = 0; i < Nb_num; i++)
    {
        Untype->Numero = g_list_append(Untype->Numero, g_strdup(contact_data->data));
        contact_data = contact_data = contact_data->next;
    }

    Untype->Anniv = g_strdup(contact_data->data);
    assert(Untype->Anniv);
    contact_data = contact_data->next;

    Untype->Adresse = g_strdup(contact_data->data);
    assert(Untype->Adresse);
    contact_data = contact_data->next;

    Untype->Notes = g_strdup(contact_data->data);
    assert(Untype->Notes);
    contact_data = contact_data->next;

    g_hash_table_insert(_Contact_list, g_strconcat(Untype->Name," ",Untype->Prenom), Untype);
    _Current_Contact = Untype;
}

void modify_contact(GList *contact_data)
{
    gchar *Nb_num_char;
    gint Nb_num = 0;
    //TODO Modifier
    _Current_Contact->Name = g_strdup(contact_data->data);
    assert(_Current_Contact->Name);
    contact_data = contact_data->next;

    _Current_Contact->Prenom = g_strdup(contact_data->data);
    assert(_Current_Contact->Prenom);
    contact_data = contact_data->next;

    _Current_Contact->Email = g_strdup(contact_data->data);
    assert(_Current_Contact->Email);
    contact_data = contact_data->next;
    
    Nb_num_char = g_strdup(contact_data->data);
    assert(Nb_num_char);

    Nb_num = g_ascii_strtoll(Nb_num_char, NULL, 10);

    contact_data = contact_data->next;

    for (gint i = 0; i < Nb_num; i++)
    {
        _Current_Contact->Numero = g_list_append(_Current_Contact->Numero, g_strdup(contact_data->data));
        contact_data = contact_data->next;
    }

    _Current_Contact->Anniv = g_strdup(contact_data->data);
    assert(_Current_Contact->Anniv);
    contact_data = contact_data->next;

    _Current_Contact->Adresse = g_strdup(contact_data->data);
    assert(_Current_Contact->Adresse);
    contact_data = contact_data->next;

    _Current_Contact->Notes = g_strdup(contact_data->data);
    assert(_Current_Contact->Notes);
    contact_data = contact_data->next;

    g_hash_table_insert(_Contact_list,g_strconcat(_Current_Contact->Name," ",_Current_Contact->Prenom), _Current_Contact);
}

void lookup_Contact(gchar *key)
{
    _Current_Contact = g_hash_table_lookup(_Contact_list, key);
}

void del_contact()
{
    g_hash_table_remove(_Contact_list, g_strconcat(_Current_Contact->Name," ",_Current_Contact->Prenom));
    g_free(_Current_Contact->Name);
    g_free(_Current_Contact->Prenom);
    g_free(_Current_Contact->Email);
    g_free(_Current_Contact->Adresse);
    g_free(_Current_Contact->Anniv);
    g_free(_Current_Contact->Notes);
    g_list_free(_Current_Contact->Numero);
    _Current_Contact = NULL;
}

Contact_t* current_contact(){
    Contact_t* Untype = _Current_Contact;
    return Untype;
}

GList *list_contact_sorted()
{
    GList *Contact_list_to_print = NULL;
    Contact_t *to_add = NULL;

    for (GList *encours = g_hash_table_get_values(_Contact_list);
         encours != NULL;
         encours = encours->next)
    {
        to_add = encours->data;
        Contact_list_to_print = g_list_insert_sorted(Contact_list_to_print, g_strdup(g_strconcat(to_add->Name," ",to_add->Prenom)), (GCompareFunc)g_strcmp0);
    }
    return Contact_list_to_print;
}
