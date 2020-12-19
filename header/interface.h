#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "data_base.h"
#include "utility_func.h"

//! { DIBASSI Brahima} 19005521 \\\\  
//! { KANOUTE Daouda} 19000407}  \\
//! \date {Dimanche 20 Décembre 2020}

static GtkWidget *listView;
static GHashTable *hashContact;
static GtkTreeSelection *selection;
static GtkWidget *number_of_contact;
static guint nb_contact = 0;

enum
{

    NAME_COLUMN,
    LAST_NAME_COLUMN,
    NUMBER_COLUMN,
    N_COLUMN
};

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

static void updateLabel(GtkLabel *label);
static void initList(GtkWidget *listViewe, GtkListStore *listStore, GtkBuilder *builder);
static void add_to_list(GtkWidget *widget, gpointer user_data);
static void ShowModal();
static void Search(GtkWidget *search_bar);
static void remove_item(GtkWidget *widget);
static void details_view(GtkWidget *widget, gpointer contact);
static void Edit_mode();
static void contact_book_quit(GtkWidget *widget);
