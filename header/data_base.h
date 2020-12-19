#include <sqlite3.h>
#include <gtk/gtk.h>
#include <assert.h>

//! { DIBASSI Brahima} 19005521 \\\\  
//! { KANOUTE Daouda} 19000407}  \\
//! \date {Dimanche 20 Décembre 2020}

static sqlite3 *_db;
#define CONTACT_SIZE ((guint8)9)

extern void data_base_init();
extern void data_base_close();
extern void data_base_add_contact(GList *un_type);
extern void data_base_del_contact(gchar *id);
extern void data_base_modify_contact(GList *un_type);
extern GList *data_base_lookup(gchar *recherche);
extern int print_data_callback();
extern void data_base_print();
extern GList *data_base_retrive();
extern void data_base_clear();