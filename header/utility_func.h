#include <gtk/gtk.h>
#include <assert.h>

//! { DIBASSI Brahima} 19005521 \\\\  
//! { KANOUTE Daouda} 19000407}  \\
//! \date {Dimanche 20 Décembre 2020}

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

extern gboolean is_str_void(gchar *to_test);
extern t_contact_hash *cast_glist_to_contact(GList *contact);
extern GList *cast_contact_to_glist(t_contact_hash *contact);
extern int compare_contact(t_contact_hash *contact_a, t_contact_hash *contact_b);
extern void hide_widget(GtkWidget *widget, GtkWidget *widget_to_hide);
