//! { DIBASSI Brahima} 19005521 \\\\  
//! { KANOUTE Daouda} 19000407}  \\
//! \date {Dimanche 20 Décembre 2020} 


#include "interface.h"

static void initList(GtkWidget *listViewe, GtkListStore *listStore, GtkBuilder *builder)
{
    GtkCellRenderer *cellRenderer;
    GtkTreeViewColumn *column;
    GtkWidget *scrollView;
    GtkTreeIter iter;
    gchar column_names[3][10] = {"prenom", "nom", "numero"};
    GList *contact_list = NULL;
    GList *UnType = NULL;
    t_contact_hash *un_contact = NULL;

    scrollView = GTK_WIDGET(gtk_builder_get_object(builder, "contact_list"));
    cellRenderer = gtk_cell_renderer_text_new();
    for (guint i = 0; i < 3; i++)
    {
        column = gtk_tree_view_column_new_with_attributes(column_names[i],
                                                          cellRenderer,
                                                          "text", i,
                                                          NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);
    }

    // Gestion auto du scroll
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollView),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollView), listView);
    listStore = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(listView),
                            GTK_TREE_MODEL(listStore));

    for (GList *encours = data_base_retrive(); encours != NULL; encours = encours->next)
    {
        UnType = encours->data;
        contact_list = g_list_append(contact_list, cast_glist_to_contact(UnType));
    }

    for (GList *contact = contact_list; contact != NULL; contact = contact->next)
    {
        un_contact = contact->data;
        gchar *key = g_strdup(g_strconcat(un_contact->Nom, un_contact->Prenom, un_contact->number1, NULL));
        g_hash_table_insert(hashContact, key, un_contact);
        gtk_list_store_append(listStore, &iter);
        gtk_list_store_set(listStore, &iter,
                           NAME_COLUMN, un_contact->Prenom,
                           LAST_NAME_COLUMN, un_contact->Nom,
                           NUMBER_COLUMN, un_contact->number1,
                           -1);
        nb_contact = g_hash_table_size(hashContact);
    }
    updateLabel(GTK_LABEL(number_of_contact));
    data_base_clear();
}

static void add_to_list(GtkWidget *widget, gpointer user_data)
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

    if (is_str_void(prenom) || is_str_void(nom) ||
        (is_str_void(number1) && is_str_void(number2) && is_str_void(number3)))
    {
        g_print("Contact non valide certains des champs obligatoires sont vides\n");
        GtkBuilder *builder = gtk_builder_new_from_file("./projetGTK.glade");
        GtkWidget *Add_error = GTK_WIDGET(gtk_builder_get_object(builder, "Add_error"));
        gtk_dialog_run(GTK_DIALOG(Add_error));
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

    gchar *key = g_strconcat(nom, prenom, number1, NULL);
    g_hash_table_insert(hashContact, key, new);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       NAME_COLUMN, prenom,
                       LAST_NAME_COLUMN, nom,
                       NUMBER_COLUMN, number1,
                       -1);
    nb_contact = g_hash_table_size(hashContact);
    updateLabel(GTK_LABEL(number_of_contact));
}

static void ShowModal()
{
    GtkBuilder *builder = NULL;
    GtkWidget *Add_user;
    GtkWidget *Cancel;
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
    Cancel = GTK_WIDGET(gtk_builder_get_object(builder, "Cancel"));
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
    g_signal_connect(Add_user, "clicked", G_CALLBACK(hide_widget), Dialog_box);
    g_signal_connect(Cancel, "clicked", G_CALLBACK(hide_widget), Dialog_box);
    gtk_dialog_run(GTK_DIALOG(Dialog_box));
}


static void details_view(GtkWidget *widget, gpointer contact)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *value;
    gchar *value1;
    gchar *value2;
    t_contact *data = contact;
    t_contact_hash *nouve;

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(widget), &model, &iter))
    {

        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        gtk_tree_model_get(model, &iter, NAME_COLUMN, &value1, -1);
        gtk_tree_model_get(model, &iter, NUMBER_COLUMN, &value2, -1);
        gchar *key = g_strconcat(value, value1, value2, NULL);

        nouve = g_hash_table_lookup(hashContact, key);
        gtk_label_set_text(GTK_LABEL(data->Nom), nouve->Nom);
        gtk_label_set_text(GTK_LABEL(data->Prenom), nouve->Prenom);
        gtk_label_set_text(GTK_LABEL(data->Adress), nouve->Adress);
        gtk_label_set_text(GTK_LABEL(data->Mail), nouve->Mail);
        gtk_label_set_text(GTK_LABEL(data->cp), nouve->cp);
        gtk_label_set_text(GTK_LABEL(data->type), nouve->type);
        gtk_label_set_text(GTK_LABEL(data->number1), nouve->number1);
        gtk_label_set_text(GTK_LABEL(data->number2), nouve->number2);
        gtk_label_set_text(GTK_LABEL(data->number3), nouve->number3);
    }
}

static void remove_item(GtkWidget *widget)
{
    GtkListStore *listStore;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *value;
    gchar *value1;
    gchar *value2;
    listStore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(listView)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(listView));

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
                                        &model, &iter))
    {
        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        gtk_tree_model_get(model, &iter, NAME_COLUMN, &value1, -1);
        gtk_tree_model_get(model, &iter, NUMBER_COLUMN, &value2, -1);
        gchar *key = g_strconcat(value, value1, value2, NULL);
        g_hash_table_remove(hashContact, key);
        gtk_list_store_remove(listStore, &iter);
        g_free(key);
    }
    nb_contact = g_hash_table_size(hashContact);
    updateLabel(GTK_LABEL(number_of_contact));
    g_free(value);
    g_free(value1);
    g_free(value2);
}

static void Edit_mode()
{
    GtkBuilder *builder = NULL;
    t_contact_hash *nouve;
    GtkTreeIter iter;
    gchar *value;
    gchar *value1;
    gchar *value2;
    GtkTreeModel *model;
    t_contact *data = g_try_malloc(sizeof(t_contact));
    builder = gtk_builder_new_from_file("./projetGTK.glade");
    GtkWidget *Edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_button"));
    GtkWidget *Last_name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Last_name_edit"));
    GtkWidget *Name_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Name_edit"));
    GtkWidget *Email_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Email_edit"));
    GtkWidget *cp_edit = GTK_WIDGET(gtk_builder_get_object(builder, "cp_edit"));
    GtkWidget *Adress_edit = GTK_WIDGET(gtk_builder_get_object(builder, "Adress_edit"));
    GtkWidget *type_edit = GTK_WIDGET(gtk_builder_get_object(builder, "type_edit"));
    GtkWidget *numero1_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero1_edit"));
    GtkWidget *numero2_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero2_edit"));
    GtkWidget *numero3_edit = GTK_WIDGET(gtk_builder_get_object(builder, "numero3_edit"));

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(selection), &model, &iter))
    {

        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        gtk_tree_model_get(model, &iter, NAME_COLUMN, &value1, -1);
        gtk_tree_model_get(model, &iter, NUMBER_COLUMN, &value2, -1);
        gchar *key = g_strconcat(value, value1, value2, NULL);
        nouve = g_hash_table_lookup(hashContact, key);
        gtk_entry_set_text(GTK_ENTRY(Last_name_edit), nouve->Nom);
        gtk_entry_set_text(GTK_ENTRY(Name_edit), nouve->Prenom);
        gtk_entry_set_text(GTK_ENTRY(Email_edit), nouve->Mail);
        gtk_entry_set_text(GTK_ENTRY(cp_edit), nouve->cp);
        gtk_combo_box_set_active(GTK_COMBO_BOX(type_edit), nouve->type_id);
        gtk_entry_set_text(GTK_ENTRY(Adress_edit), nouve->Adress);
        gtk_entry_set_text(GTK_ENTRY(numero1_edit), nouve->number1);
        gtk_entry_set_text(GTK_ENTRY(numero2_edit), nouve->number2);
        gtk_entry_set_text(GTK_ENTRY(numero3_edit), nouve->number3);
    }

    data->Prenom = Name_edit;
    data->Nom = Last_name_edit;
    data->Mail = Email_edit;
    data->Adress = Adress_edit;
    data->cp = cp_edit;
    data->type = type_edit;
    data->number1 = numero1_edit;
    data->number2 = numero2_edit;
    data->number3 = numero3_edit;

    GtkWidget *Edit_contact = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_contact"));
    g_signal_connect(Edit_button, "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(Edit_button, "clicked", G_CALLBACK(add_to_list), data);
    g_signal_connect(Edit_button, "clicked", G_CALLBACK(hide_widget), Edit_contact);

    gtk_dialog_run(GTK_DIALOG(Edit_contact));
    g_free(value);
    g_free(value1);
    g_free(value2);
}

static void Search(GtkWidget *widget, gpointer search_bar)
{
    gchar *entry = g_strdup(gtk_entry_get_text(GTK_ENTRY(search_bar)));
    GList *all_contact = g_hash_table_get_values(hashContact);
    all_contact = g_list_sort(all_contact, (GCompareFunc)compare_contact);
    GList *search_result = NULL;
    guint entry_len = strlen(entry);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *value;
    gchar *value1;
    gchar *value2;
    t_contact_hash *UnType;
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(listView));
    for (GList *encours = all_contact; encours != NULL; encours = encours->next)
    {
        UnType = encours->data;
        if (g_ascii_strncasecmp(entry, UnType->Nom, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->Prenom, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number1, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number2, entry_len) == 0 ||
            g_ascii_strncasecmp(entry, UnType->number3, entry_len) == 0)
        {

            search_result = g_list_append(search_result, UnType);
        }
    }

    for (guint indice = 0; indice < nb_contact; indice++)
    {
        gtk_tree_model_get_iter_from_string(model, &iter, g_strdup_printf("%i", indice));
        gtk_tree_selection_select_iter(selection, &iter);
        gtk_tree_model_get(model, &iter, LAST_NAME_COLUMN, &value, -1);
        gtk_tree_model_get(model, &iter, NAME_COLUMN, &value1, -1);
        gtk_tree_model_get(model, &iter, NUMBER_COLUMN, &value2, -1);
        gchar *key = g_strconcat(value1, value, value2, NULL);

        for (GList *encours = search_result; encours != NULL; encours = encours->next)
        {
            UnType = encours->data;
            gchar *result_key = g_strconcat(UnType->Prenom, UnType->Nom, UnType->number1, NULL);
            if (g_strcmp0(result_key, key) == 0)
            {
                return;
            }
            g_free(result_key);
        }
        g_free(key);
    }
    gtk_tree_model_get_iter_first(model, &iter);
    gtk_tree_selection_select_iter(selection, &iter);
}


static void contact_book_quit(GtkWidget *widget)
{
    GList *all_contact = NULL;
    GList *UnType = NULL;
    for (all_contact = g_hash_table_get_values(hashContact); all_contact != NULL; all_contact = all_contact->next)
    {
        UnType = cast_contact_to_glist((t_contact_hash *)all_contact->data);
        data_base_add_contact(UnType);
    }
    g_hash_table_unref(hashContact);
    data_base_close();
    gtk_main_quit();
}

static void updateLabel(GtkLabel *label)
{
    gchar *display;
    display = g_strdup_printf("%d", nb_contact);   //convert num to str
    gtk_label_set_text(GTK_LABEL(label), display); //set label to "display"
    g_free(display);                               //free display
}

gint main(gint argc, gchar **argv)
{
    data_base_init();
    GtkBuilder *builder = NULL;
    GtkListStore *listStore;

    t_contact *contact = g_try_malloc(sizeof(t_contact));
    gtk_init(&argc, &argv);

    hashContact = g_hash_table_new(g_str_hash, g_str_equal);
    // fichier Glade
    builder = gtk_builder_new_from_file("./projetGTK.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));

    // Initialiser les elements  glade

    GtkWidget *contact_new = GTK_WIDGET(gtk_builder_get_object(builder, "contact_new"));
    GtkWidget *contact_remove = GTK_WIDGET(gtk_builder_get_object(builder, "contact_remove"));
    GtkWidget *user_name_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_name_right"));
    GtkWidget *user_last_name_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_first_name_right"));
    GtkWidget *user_cp_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_cp_right"));
    GtkWidget *user_type_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_type_right"));
    GtkWidget *user_email_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_email_right"));
    GtkWidget *user_adress_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_adress_right"));
    GtkWidget *user_number1_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number1_right"));
    GtkWidget *user_number2_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number2_right"));
    GtkWidget *user_number3_right = GTK_WIDGET(gtk_builder_get_object(builder, "user_number3_right"));
    GtkWidget *search_bar = GTK_WIDGET(gtk_builder_get_object(builder, "search_bar"));
    GtkWidget *Edit_contact_btn = GTK_WIDGET(gtk_builder_get_object(builder, "Edit_contact_btn"));
    number_of_contact = GTK_WIDGET(gtk_builder_get_object(builder, "number_of_contact"));

    updateLabel(GTK_LABEL(number_of_contact));

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

    initList(listView, listStore, builder);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listView));

    g_signal_connect(G_OBJECT(window), "destroy", (GCallback)contact_book_quit, NULL);
    g_signal_connect(contact_new, "clicked", G_CALLBACK(ShowModal), NULL);
    g_signal_connect(contact_remove, "clicked", G_CALLBACK(remove_item), selection);
    g_signal_connect(selection, "changed", G_CALLBACK(details_view), contact);
    g_signal_connect(Edit_contact_btn, "clicked", G_CALLBACK(Edit_mode), NULL);
    g_signal_connect(search_bar, "changed", G_CALLBACK(Search), search_bar);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
