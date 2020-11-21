#include <gtk/gtk.h>

typedef struct Contact
{
    gchar *Name;
    gchar *Prenom;
    gchar *Email;
    GList *Numero;
    gchar *Anniv;
    gchar *Adresse;
    gchar *Notes;
} Contact_t;


GHashTable *_Contact_list = NULL;
Contact_t *_Current_Contact = NULL;

void global_list_init();
void init_contact(GList* contact_data);
void modify_contact(GList* contact_data);
void lookup_Contact(gchar *name);
void del_contact(void);
