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

typedef struct Contact_struct
{
    gchar *Nom;
    gchar *Prenom;
    gchar *cp;
    gchar *number;
} t_contact;

t_contact Newcontact(gchar *Prenom, gchar *Nom, gchar *cp, gchar *number)
{
    t_contact contact;
    contact.Prenom = Prenom;
    contact.Nom = Nom;
    contact.cp = cp;
    contact.number = number;
    return contact;
}

void ShowModal()
{
    GtkBuilder *builder = NULL;
    gchar *filename = NULL;
    builder = gtk_builder_new();
    filename = g_build_filename("./projetGTK.glade", NULL);
    gtk_builder_add_from_file(builder, filename, NULL);
    GtkWidget *Dialog_box;
    Dialog_box = GTK_WIDGET(gtk_builder_get_object(builder, "Dialog_box"));

    gtk_widget_show_all(Dialog_box);
}

void GetInformation()
{
    printf("lalal\n");
}
gint main(gint argc, gchar **argv)
{
    GtkBuilder *builder = NULL;
    GtkListStore *listStore;
    GtkWidget *listView;
    GtkWidget *scrollView;
    GtkCellRenderer *cellRenderer;
    gchar *txt;
    gint i;
    GtkTreeViewColumn *column;
    GtkWidget *window;
    GtkWidget *contact_list;
    GtkWidget *contact_new;
    GtkWidget *New_user_name;
    GtkWidget *New_user_last_name;
    GtkWidget *New_user_number;
    GtkWidget *Add_user;
    GError *error = NULL;
    gchar *filename = NULL;
    gtk_init(&argc, &argv);
    t_contact daouda = Newcontact("daouda", "kanoute", "00000", "0617171717");
    // fichier Glade
    builder = gtk_builder_new();
    filename = g_build_filename("./projetGTK.glade", NULL);
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));

    // Initialiser les elements  glade
    contact_list = GTK_WIDGET(gtk_builder_get_object(builder, "contact_list"));
    contact_new = GTK_WIDGET(gtk_builder_get_object(builder, "contact_new"));
    Add_user = GTK_WIDGET(gtk_builder_get_object(builder, "Add_user"));
    New_user_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_name"));
    New_user_last_name = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_last_name"));
    New_user_number = GTK_WIDGET(gtk_builder_get_object(builder, "New_user_number"));
    scrollView = GTK_WIDGET(gtk_builder_get_object(builder, "contact_list"));

    /* listStore */
    listStore = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    txt = g_malloc(12);
    for (i = 0; i < 30; ++i)
    {
        GtkTreeIter pIter;

        /* Creation de la nouvelle ligne */
        gtk_list_store_append(listStore, &pIter);

        /* Mise a jour des donnees */
        gtk_list_store_set(listStore, &pIter,
                           NAME_COLUMN, daouda.Prenom,
                           LAST_NAME_COLUMN, daouda.Nom,
                           CP_COLUMN, daouda.cp,
                           NUMBER_COLUMN, daouda.number,
                           -1);
    }
    g_free(txt);

    listView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
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

    // Initialisation de la fenetre
    g_signal_connect(G_OBJECT(window), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect(contact_new, "clicked", G_CALLBACK(ShowModal), NULL);
    g_signal_connect(Add_user, "clicked", G_CALLBACK(GetInformation), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}