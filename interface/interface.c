#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

enum
{

    NAME_COLUMN,
    LAST_NAME_COLUMN,
    N_COLUMN
};
GtkWidget *listView;
GHashTable *hashContact;
gint *id = 0;
typedef struct Contact_struct
{
    guint *unit;
    GtkWidget *Nom;
    GtkWidget *Prenom;
    GtkWidget *Mail;
    GtkWidget *Adress;
    GtkWidget *cp;
    GtkWidget *number1;
    GtkWidget *number2;
    GtkWidget *number3;
} t_contact;

typedef struct Contact_hash_struct
{
    guint unit;
    gchar *Nom;
    gchar *Prenom;
    gchar *Mail;
    gchar *Adress;
    gchar *cp;
    gchar *number1;
    gchar *number2;
    gchar *number3;
} t_contact_hash;

void initList(GtkWidget *listViewe, GtkListStore *listStore, GtkBuilder *builder)
{
    GtkCellRenderer *cellRenderer;
    GtkTreeViewColumn *column;
    GtkWidget *scrollView;

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
    guint id = g_hash_table_size(hashContact);
    new->unit = id;
    new->Prenom = prenom;
    new->Nom = nom;
    new->cp = cp;
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
    GtkWidget *Dialog_box = GTK_WIDGET(gtk_builder_get_object(builder, "Dialog_box"));
    Add_user = GTK_WIDGET(gtk_builder_get_object(builder, "Add_user"));
    contact->unit = id;
    contact->Prenom = New_user_name;
    contact->Nom = New_user_last_name;
    contact->Mail = New_user_email;
    contact->Adress = New_user_adress;
    contact->cp = New_user_cp;
    contact->number1 = New_user_number1;
    contact->number2 = New_user_number2;
    contact->number3 = New_user_number3;
    id++;

    g_signal_connect(Add_user, "clicked", G_CALLBACK(add_to_list), contact);
    gtk_dialog_run(GTK_DIALOG(Dialog_box));
}

gint compare_contact(t_contact_hash* contact_a,t_contact_hash* contact_b){
    gchar* A_full_name = g_strjoin("",contact_a->Nom,contact_a->Prenom,NULL);
    gchar* B_full_name = g_strjoin("",contact_b->Nom,contact_b->Prenom,NULL);
    return g_strcmp0(A_full_name,B_full_name);
}


void search_view(GtkWidget *search_bar, gpointer data)
{
    gchar *entry = g_strdup(gtk_entry_get_text(GTK_ENTRY(search_bar)));
    GList *all_contact = g_hash_table_get_values(hashContact);
    all_contact = g_list_sort(all_contact,(GCompareFunc)compare_contact);
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

            g_print("%s\n", (gchar *)UnType->Nom);
            //TODO Faire un machin avec UnType
        }
    }
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
        gtk_label_set_text(GTK_LABEL(data->number1), nouve->number1);
        gtk_label_set_text(GTK_LABEL(data->number2), nouve->number2);
        gtk_label_set_text(GTK_LABEL(data->number3), nouve->number3);
        g_free(value);
    }
}
gint main(gint argc, gchar **argv)
{
    GtkBuilder *builder = NULL;
    GtkListStore *listStore;
    gchar *txt;
    GtkWidget *window;
    GtkWidget *contact_list;
    GtkWidget *contact_new;
    GtkWidget *contact_remove;
    GtkWidget *user_name_right;
    GError *error = NULL;
    gchar *filename = NULL;
    GtkWidget *user_last_name_right;
    GtkWidget *user_cp_right;
    GtkWidget *user_email_right;
    GtkWidget *user_adress_right;
    GtkWidget *user_number1_right;
    GtkWidget *user_number2_right;
    GtkWidget *user_number3_right;
    GtkWidget *search_bar;
    GtkTreeSelection *selection;
    t_contact *contact = g_try_malloc(sizeof(t_contact));

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
    user_email_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_email_right"));
    user_adress_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_adress_right"));
    user_number1_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number1_right"));
    user_number2_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number2_right"));
    user_number3_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number3_right"));
    search_bar = GTK_WIDGET(gtk_builder_get_object(builder, "search_bar"));
    GtkWidget *Dialog_box = GTK_WIDGET(gtk_builder_get_object(builder, "Dialog_box"));

    // vue de droite
    contact->Prenom = user_name_right;
    contact->Nom = user_last_name_right;
    contact->Mail = user_email_right;
    contact->Adress = user_adress_right;
    contact->cp = user_cp_right;
    contact->number1 = user_number1_right;
    contact->number2 = user_number2_right;
    contact->number3 = user_number3_right;
    listView = gtk_tree_view_new();

    initList(listView, listStore, builder);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listView));

    g_signal_connect(G_OBJECT(window), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect(contact_new, "clicked", G_CALLBACK(ShowModal), NULL);
    g_signal_connect(G_OBJECT(contact_remove), "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(selection, "changed", G_CALLBACK(details_view), contact);
    g_signal_connect(search_bar, "search-changed", G_CALLBACK(search_view), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

//TODO Search button callback BIBI sauf pour "le popup ou equivalent"
//TODO Modify bouton + callback
//TODO Ajout gestion data base START and QUIT
//TODO REparer le btn type