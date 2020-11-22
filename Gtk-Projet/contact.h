#include <gtk/gtk.h>
#include <assert.h>

//TODO Passer sur une liste
typedef struct Contact
{
    gchar *Name;
    gchar *Prenom;
    gchar *Email;
    gchar *Anniv;
    gchar *Adresse;
    gchar *Notes;
    GList *Numero;
} Contact_t;


GHashTable *_Contact_list = NULL;
Contact_t *_Current_Contact = NULL;

void global_list_init(gchar *filename);
void init_contact(GList* contact_data);
void modify_contact(GList* contact_data);
void lookup_Contact(gchar *name);
void del_contact(void);
GList *list_contact_sorted();
