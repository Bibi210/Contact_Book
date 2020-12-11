#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "data_base.h"
enum
{

    NAME_COLUMN,
    LAST_NAME_COLUMN,
    N_COLUMN
};
GtkWidget *listView;
GHashTable *hashContact;
gint *id = 0;
GtkTreeSelection *selection;

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

typedef struct
{
    GtkTreeSelection *selection;
    t_contact *Edit_contact;
} t_edit;
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
} t_contact_hash;

t_contact_hash *cast_glist_to_contact(GList *contact)
{
    t_contact_hash *UnType = g_try_malloc0(sizeof(t_contact_hash));
    assert(UnType);
    UnType->Nom = g_strdup(g_list_nth_data(contact, 0));
    UnType->Prenom = g_strdup(g_list_nth_data(contact, 1));
    UnType->Mail = g_strdup(g_list_nth_data(contact, 2));
    UnType->Adress = g_strdup(g_list_nth_data(contact, 3));
    UnType->cp = g_strdup(g_list_nth_data(contact, 4));
    UnType->type = g_strdup(g_list_nth_data(contact, 5));
    UnType->number1 = g_strdup(g_list_nth_data(contact, 6));
    UnType->number2 = g_strdup(g_list_nth_data(contact, 7));
    UnType->number3 = g_strdup(g_list_nth_data(contact, 8));
    return UnType;
}

void initList(GtkWidget *listViewe, GtkListStore *listStore, GtkBuilder *builder)
{
    GtkCellRenderer *cellRenderer;
    GtkTreeViewColumn *column;
    GtkWidget *scrollView;
    GtkTreeIter iter;

    scrollView = GTK_WIDGET(gtk_builder_get_object(builder, "contact_list"));
    cellRenderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("prenom",
                                                      cellRenderer,
                                                      "text", NAME_COLUMN,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);
    column = gtk_tree_view_column_new_with_attributes("nom",
                                                      cellRenderer,
                                                      "text", LAST_NAME_COLUMN,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);

    // Gestion auto du scroll
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollView),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollView), listView);
    listStore = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listView),
                            GTK_TREE_MODEL(listStore));

    GList *contact_list = NULL;
    GList *UnType = NULL;
    for (GList *encours = data_base_retrive(); encours != NULL; encours = encours->next)
    {
        UnType = encours->data;
        contact_list = g_list_append(contact_list, cast_glist_to_contact(UnType));
    }
    t_contact_hash *un_contact = NULL;
    for (GList *contact = contact_list; contact != NULL; contact = contact->next)
    {
        un_contact = contact->data;
        gchar *key = g_strdup(g_strconcat(un_contact->Prenom, un_contact->Nom, NULL));
        g_hash_table_insert(hashContact, key, un_contact);
        gtk_list_store_append(listStore, &iter);
        gtk_list_store_set(listStore, &iter,
                           NAME_COLUMN, un_contact->Prenom,
                           LAST_NAME_COLUMN, un_contact->Nom,
                           -1);
    }
}

gboolean is_str_void(gchar *to_test)
{
    if (g_strcmp0(to_test, "") == 0)
    {
        return TRUE;
    }
    return FALSE;
}

void add_to_list(GtkWidget *widget, gpointer user_data)
{

    GtkListStore *store;
    GtkTreeIter iter;
    t_contact *d = user_data;
    t_contact_hash *new = g_try_malloc(sizeof(t_contact_hash));
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(listView)));
    gchar *prenom = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Prenom)));
    gchar *nom = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Nom)));
    gchar *cp = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->cp)));
    gchar *adress = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Adress)));
    gchar *mail = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Mail)));
    gchar *number1 = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->number1)));
    gchar *number2 = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->number2)));
    gchar *number3 = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->number3)));
    gchar *type = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(d->type));
    guint id = g_hash_table_size(hashContact);

    if (is_str_void(prenom) || is_str_void(nom) ||
        (is_str_void(number1) && is_str_void(number2) && is_str_void(number3)))
    {
        g_print("Contact non valide certains des champs obligatoires sont vides\n");
        //? TODO Pop up ?
        return;
    }

    new->Prenom = prenom;
    new->Nom = nom;
    new->cp = cp;
    new->type = type;
    new->Adress = adress;
    new->Mail = mail;
    new->number1 = number1;
    new->number2 = number2;
    new->number3 = number3;
    g_hash_table_insert(hashContact, nom, new);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       NAME_COLUMN, prenom,
                       LAST_NAME_COLUMN, nom,
                       -1);
    g_print("%d\n", id);
}

void ShowModal()
{
    GtkBuilder *builder = NULL;
    GtkWidget *Add_user;
    GtkWidget *New_user_name;
    GtkWidget *New_user_last_name;
    GtkWidget *New_user_cp;
    GtkWidget *New_user_email;
    GtkWidget *New_user_adress;
    GtkWidget *New_user_number1;
    GtkWidget *New_user_number2;
    GtkWidget *New_user_number3;
    GtkWidget *New_user_type;
    t_contact *contact = g_try_malloc(sizeof(t_contact));

    //  Element graphique Glade
    builder = gtk_builder_new_from_file("./projetGTK.glade");
    New_user_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_name"));
    New_user_last_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_last_name"));
    New_user_cp = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_cp"));
    New_user_email = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_email"));
    New_user_adress = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_adress"));
    New_user_number1 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number1"));
    New_user_number2 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number2"));
    New_user_number3 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number3"));
    New_user_type = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_type"));
    GtkWidget *Dialog_box = GTK_WIDGET(gtk_builder_get_object(builder, "Dialog_box"));
    Add_user = GTK_WIDGET(gtk_builder_get_object(builder, "Add_user"));
    contact->Prenom = New_user_name;
    contact->Nom = New_user_last_name;
    contact->Mail = New_user_email;
    contact->Adress = New_user_adress;
    contact->cp = New_user_cp;
    contact->type = New_user_type;
    contact->number1 = New_user_number1;
    contact->number2 = New_user_number2;
    contact->number3 = New_user_number3;
    g_signal_connect(Add_user, "clicked", G_CALLBACK(add_to_list), contact);
    gtk_dialog_run(GTK_DIALOG(Dialog_box));
}

gint compare_contact(t_contact_hash *contact_a, t_contact_hash *contact_b)
{
    gchar *A_full_name = g_strjoin("", contact_a->Nom, contact_a->Prenom, NULL);
    gchar *B_full_name = g_strjoin("", contact_b->Nom, contact_b->Prenom, NULL);
    return g_strcmp0(A_full_name, B_full_name);
}
//! Solve This shit
void search_view(gchar *entry)
{
    GList *all_contact = g_hash_table_get_values(hashContact);
    all_contact = g_list_sort(all_contact, (GCompareFunc)compare_contact);
    GList *search_result = NULL;
    guint entry_len = strlen(entry);
    for (GList *encours = all_contact; encours != NULL; encours = encours->next)
    {
        t_contact_hash *UnType = encours->data;
        if (g_ascii_strncasecmp(entry, UnType->Nom, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->Prenom, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number1, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number2, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number3, entry_len) == 0)
        {

            search_result = g_list_append(search_result, UnType);
        }
    }
    //TODO things with search_result
}

void Search(GtkWidget *btn, gpointer search_bar)
{
    gchar *entry = g_strdup(gtk_entry_get_text(GTK_ENTRY(search_bar)));
    search_view(entry);
}

void remove_item(GtkWidget *widget, gpointer selection)
{
    GtkListStore *listStore;
    GtkTreeModel *model;
    GtkTreeIter iter;

    listStore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(listView)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(listView));

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
                                        &model, &iter))
    {
        gtk_list_store_remove(listStore, &iter);
    }
}

void details_view(GtkWidget *widget, gpointer contact)
{

    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *value;
    t_contact *data = contact;
    t_contact_hash *nouve;

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(widget), &model, &iter))
    {

        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        nouve = g_hash_table_lookup(hashContact, value);
        gtk_label_set_text(GTK_LABEL(data->Nom), nouve->Nom);
        gtk_label_set_text(GTK_LABEL(data->Prenom), nouve->Prenom);
        gtk_label_set_text(GTK_LABEL(data->Adress), nouve->Adress);
        gtk_label_set_text(GTK_LABEL(data->Mail), nouve->Mail);
        gtk_label_set_text(GTK_LABEL(data->cp), nouve->cp);
        gtk_label_set_text(GTK_LABEL(data->type), nouve->type);
        gtk_label_set_text(GTK_LABEL(data->number1), nouve->number1);
        gtk_label_set_text(GTK_LABEL(data->number2), nouve->number2);
        gtk_label_set_text(GTK_LABEL(data->number3), nouve->number3);
        g_free(value);
    }
}

void Edit_mode()
{
    GtkBuilder *builder = NULL;
    t_contact_hash *nouve;
    GtkTreeIter iter;
    gchar *value;
    GtkTreeModel *model;
    t_contact *data = g_try_malloc(sizeof(t_contact));
    builder = gtk_builder_new_from_file("./projetGTK.glade");
    GtkWidget *Edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_button"));
    GtkWidget *Last_name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Last_name_edit"));
    GtkWidget *Name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Name_edit"));
    GtkWidget *Email_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Email_edit"));
    GtkWidget *cp_edit = GTK_WIDGET(gtk_builder_get_object(builder, "cp_edit"));
    GtkWidget *Adress_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Adress_edit"));
    GtkWidget *numero1_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero1_edit"));
    GtkWidget *numero2_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero2_edit"));
    GtkWidget *numero3_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero3_edit"));

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(selection), &model, &iter))
    {

        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        nouve = g_hash_table_lookup(hashContact, value);
        gtk_entry_set_text(GTK_ENTRY(Last_name_edit), nouve->Nom);
        gtk_entry_set_text(GTK_ENTRY(Name_edit), nouve->Nom);
        gtk_entry_set_text(GTK_ENTRY(Email_edit), nouve->Mail);
        gtk_entry_set_text(GTK_ENTRY(cp_edit), nouve->Adress);
        gtk_entry_set_text(GTK_ENTRY(Adress_edit), nouve->cp);
        gtk_entry_set_text(GTK_ENTRY(numero1_edit), nouve->number1);
        gtk_entry_set_text(GTK_ENTRY(numero2_edit), nouve->number2);
        gtk_entry_set_text(GTK_ENTRY(numero3_edit), nouve->number3);
    }

    data->Prenom = Name_edit;
    data->Nom = Last_name_edit;
    data->Mail = Email_edit;
    data->Adress = Adress_edit;
    data->cp = cp_edit;
    data->number1 = numero1_edit;
    data->number2 = numero2_edit;
    data->number3 = numero3_edit;
    g_print("edit %s\n", gtk_entry_get_text(GTK_ENTRY(Last_name_edit)));

    GtkWidget *Edit_contact = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_contact"));
    g_signal_connect(Edit_button, "clicked", G_CALLBACK(add_to_list), data);
    g_signal_connect(Edit_button, "clicked", G_CALLBACK(remove_item), selection);

    gtk_dialog_run(GTK_DIALOG(Edit_contact));
}

GList *cast_contact_to_glist(t_contact_hash *contact)
{
    GList *contact_list = NULL;
    contact_list = g_list_append(contact_list, g_strdup(contact->Nom));
    contact_list = g_list_append(contact_list, g_strdup(contact->Prenom));
    contact_list = g_list_append(contact_list, g_strdup(contact->Mail));
    contact_list = g_list_append(contact_list, g_strdup(contact->Adress));
    contact_list = g_list_append(contact_list, g_strdup(contact->cp));
    contact_list = g_list_append(contact_list, g_strdup(contact->type));
    contact_list = g_list_append(contact_list, g_strdup(contact->number1));
    contact_list = g_list_append(contact_list, g_strdup(contact->number2));
    contact_list = g_list_append(contact_list, g_strdup(contact->number3));
    return contact_list;
}

void contact_book_quit(GtkWidget *widget, gpointer data)
{
    GList *all_contact = NULL;
    GList *UnType = NULL;
    for (all_contact = g_hash_table_get_values(hashContact); all_contact != NULL; all_contact = all_contact->next)
    {
        UnType = cast_contact_to_glist((t_contact_hash *)all_contact->data);
        data_base_add_contact(UnType);
    }

    data_base_close();
    gtk_main_quit();
}

gint main(gint argc, gchar **argv)
{
    data_base_init();
    GtkBuilder *builder = NULL;
    GtkListStore *listStore;
    GtkWidget *window;
    GtkWidget *contact_list;
    GtkWidget *contact_new;
    GtkWidget *contact_remove;
    GtkWidget *user_name_right;
    GError *error = NULL;
    gchar *filename = NULL;
    GtkWidget *user_last_name_right;
    GtkWidget *user_cp_right;
    GtkWidget *user_type_right;
    GtkWidget *user_email_right;
    GtkWidget *user_adress_right;
    GtkWidget *user_number1_right;
    GtkWidget *user_number2_right;
    GtkWidget *user_number3_right;
    GtkWidget *search_bar;
    GtkWidget *search_button;
    t_contact *contact = g_try_malloc(sizeof(t_contact));
    t_contact *newEdit = g_try_malloc(sizeof(t_contact));
    gtk_init(&argc, &argv);

    hashContact = g_hash_table_new(g_str_hash, g_str_equal);
    // fichier Glade
    builder = gtk_builder_new();
    filename = g_build_filename("./projetGTK.glade", NULL);
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));

    // Initialiser les elements  glade
    contact_list = GTK_WIDGET(gtk_builder_get_object(builder, "contact_list"));
    contact_new = GTK_WIDGET(gtk_builder_get_object(builder, "contact_new"));
    contact_remove = GTK_WIDGET(gtk_builder_get_object(builder, "contact_remove"));
    user_name_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_name_right"));
    user_last_name_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_first_name_right"));
    user_cp_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_cp_right"));
    user_type_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_type_right"));
    user_email_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_email_right"));
    user_adress_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_adress_right"));
    user_number1_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number1_right"));
    user_number2_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number2_right"));
    user_number3_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number3_right"));
    search_bar = GTK_WIDGET(gtk_builder_get_object(builder, "search_bar"));
    search_button = GTK_WIDGET(gtk_builder_get_object(builder, "search_btn"));
    GtkWidget *Edit_contact_btn = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_contact_btn"));
    GtkWidget *Last_name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "last_name_label"));
    GtkWidget *Name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "name_label"));
    GtkWidget *Email_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Email_label"));
    GtkWidget *cp_edit = GTK_WIDGET(gtk_builder_get_object(builder, "cp_label"));
    GtkWidget *Adress_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Adress_label"));
    GtkWidget *numero1_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero1_label"));
    GtkWidget *numero2_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero2_label"));
    GtkWidget *numero3_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero3_label"));
    // vue de droite
    contact->Prenom = user_name_right;
    contact->Nom = user_last_name_right;
    contact->Mail = user_email_right;
    contact->Adress = user_adress_right;
    contact->cp = user_cp_right;
    contact->type = user_type_right;
    contact->number1 = user_number1_right;
    contact->number2 = user_number2_right;
    contact->number3 = user_number3_right;
    listView = gtk_tree_view_new();
    // =================================================
    newEdit->Nom = Last_name_edit;
    newEdit->Prenom = Name_edit;
    newEdit->Mail = Email_edit;
    newEdit->cp = cp_edit;
    newEdit->Adress = Adress_edit;
    newEdit->number1 = numero1_edit;
    newEdit->number2 = numero2_edit;
    newEdit->number3 = numero3_edit;

    initList(listView, listStore, builder);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listView));

    g_signal_connect(G_OBJECT(window), "destroy", (GCallback)contact_book_quit, NULL);
    g_signal_connect(contact_new, "clicked", G_CALLBACK(ShowModal), NULL);
    g_signal_connect(contact_remove, "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(selection, "changed", G_CALLBACK(details_view), contact);
    g_signal_connect(Edit_contact_btn, "clicked", G_CALLBACK(Edit_mode), NULL);
    {
        g_signal_connect(search_button, "clicked", G_CALLBACK(Search), search_bar);
    }
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

//! BIBI
// TODO Ajout gestion data base START and QUIT
// TODO Compter les contacts

//! Daouda
//TODO Search button Pop-up
// TODO Ajouter la combobox text a Edit modal
// TODO Creer une modal pour search
// TODO Key for HashTable nom + Prenom + all_num