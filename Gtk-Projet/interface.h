#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "data_base.h"

GtkWidget *listView;
GHashTable *hashContact;
GtkTreeSelection *selection;
GtkWidget *number_of_contact;
guint nb_contact = 0;

enum
{

    NAME_COLUMN,
    LAST_NAME_COLUMN,
    NUMBER_COLUMN,
    N_COLUMN
};

typedef struct Contact_hash_struct
{
    gchar *Nom;
    gchar *Prenom;
    gchar *Mail;
    gchar *Adress;
    gchar *cp;
    gchar *type;
    gchar *number1;
    gchar *number2;
    gchar *number3;
    gint type_id;
} t_contact_hash;


typedef struct Contact_struct
{
    guint *unit;
    GtkWidget *Nom;
    GtkWidget *Prenom;
    GtkWidget *Mail;
    GtkWidget *Adress;
    GtkWidget *cp;
    GtkWidget *type;
    GtkWidget *number1;
    GtkWidget *number2;
    GtkWidget *number3;
} t_contact;


t_contact_hash *cast_glist_to_contact(GList *contact);

