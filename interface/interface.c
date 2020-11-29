#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

enum
{
    USER_NAME,
    USER_LAST_NAME,
    /* Not used by the listView, maybe used elsewhere */ /* Just to show how the listStore can affect the listView */
    N_columnS
};
enum
{

    NAME_COLUMN,
    LAST_NAME_COLUMN,
    CP_COLUMN,
    NUMBER_COLUMN,
    N_COLUMN
};
GtkWidget *listView;

typedef struct Contact_struct
{

    GtkWidget *Nom;
    GtkWidget *Prenom;
    GtkWidget *cp;
    GtkWidget *email;
    GtkWidget *adress;
    GtkWidget *number1;
    GtkWidget *number2;
    GtkWidget *number3;
    GtkWidget *note;
} t_contact;

// t_contact Newcontact(gchar *Prenom, gchar *Nom, gchar *cp, gchar *number)
// {
//     t_contact contact;
//     contact.Prenom = Prenom;
//     contact.Nom = Nom;
//     contact.cp = cp;
//     contact.number = number;
//     return contact;
// }

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

    column = gtk_tree_view_column_new_with_attributes("CP",
                                                      cellRenderer,
                                                      "text", CP_COLUMN,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);

    column = gtk_tree_view_column_new_with_attributes("Number1",
                                                      cellRenderer,
                                                      "text", NUMBER_COLUMN,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);

    // Gestion auto du scroll
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollView),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollView), listView);
    listStore = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listView),
                            GTK_TREE_MODEL(listStore));
}

void add_to_list(GtkWidget *widget, gpointer user_data)
{

    GtkListStore *store;
    GtkTreeIter iter;
    t_contact *d = user_data;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(listView)));
    gchar *prenom = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Prenom)));
    gchar *nom = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->Nom)));
    gchar *cp = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->cp)));
    gchar *number1 = g_strdup(gtk_entry_get_text(GTK_ENTRY(d->number1)));
    
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       NAME_COLUMN, prenom,
                       LAST_NAME_COLUMN, nom,
                       NUMBER_COLUMN, number1,
                       CP_COLUMN, cp,
                       -1);
}

void GetInformation(t_contact contact)
{
    printf("lalal\n");
}

void ShowModal()
{
    GtkBuilder *builder = NULL;
    t_contact *contact = g_try_malloc(sizeof(t_contact));
  

    //  const gchar *number;
    builder = gtk_builder_new_from_file("./projetGTK.glade");
     GtkWidget *Add_user = GTK_WIDGET(gtk_builder_get_object(builder, "Add_user"));
    GtkWidget *Dialog_box = GTK_WIDGET(gtk_builder_get_object(builder, "Dialog_box"));
     GtkWidget *New_user_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_name"));
     GtkWidget *New_user_last_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_last_name"));
     GtkWidget *New_user_adress = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_adress"));
     GtkWidget *New_user_cp = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_cp"));
     GtkWidget *New_user_number1 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number1"));
     GtkWidget *New_user_number2 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number2"));
     GtkWidget *New_user_number3 = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number3"));

    contact->Prenom = New_user_name;
    contact->Nom = New_user_last_name;
    contact->cp = New_user_cp;
    contact->adress = New_user_adress;
    contact->number1 = New_user_number1;
    contact->number2 = New_user_number2;
    contact->number3 = New_user_number3;

    g_signal_connect(Add_user, "clicked", G_CALLBACK(add_to_list), contact);
    gtk_dialog_run(GTK_DIALOG(Dialog_box));
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

gint main(gint argc, gchar **argv)
{
    GtkBuilder *builder = NULL;
    GtkListStore *listStore;
    gchar *txt;
    GtkWidget *window;
    GtkWidget *contact_list;
    GtkWidget *contact_new;
    GtkWidget *contact_remove;
    GError *error = NULL;
    gchar *filename = NULL;
    GtkTreeSelection *selection;
    gtk_init(&argc, &argv);

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

    /* listStore */
    listStore = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    listView = gtk_tree_view_new();

    initList(listView, listStore, builder);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listView));

    g_signal_connect(G_OBJECT(window), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect(contact_new, "clicked", G_CALLBACK(ShowModal), NULL);
    g_signal_connect(G_OBJECT(contact_remove), "clicked", G_CALLBACK(remove_item), selection);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}