#include "utility_func.h"

extern void hide_widget(GtkWidget *widget, GtkWidget *widget_to_hide)
{
    gtk_widget_hide(widget_to_hide);
};


extern gboolean is_str_void(gchar *to_test)
{
    if (g_strcmp0(to_test, "") == 0)
    {
        return TRUE;
    }
    return FALSE;
}

extern t_contact_hash *cast_glist_to_contact(GList *contact)
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

extern gint compare_contact(t_contact_hash *contact_a, t_contact_hash *contact_b)
{
    gchar *A_full_name = g_strjoin("", contact_a->Nom, contact_a->Prenom, NULL);
    gchar *B_full_name = g_strjoin("", contact_b->Nom, contact_b->Prenom, NULL);
    return g_strcmp0(A_full_name, B_full_name);
}

extern GList *cast_contact_to_glist(t_contact_hash *contact)
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