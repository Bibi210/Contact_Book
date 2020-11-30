#include <sqlite3.h>
#include <gtk/gtk.h>



#define CONTACT_SIZE ((guint8)11)

extern void data_base_init();
extern void data_base_close();
extern void data_base_add_contact(GList *un_type);
extern void data_base_del_contact(gchar *id);
extern void data_base_modify_contact(GList *un_type);
extern GList* data_base_lookup(gchar *recherche);
extern int print_data_callback();
extern void data_base_print();