#include "contact.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void show_num(GList *lst)
{
  GList *l;
  gint64 i;
  gchar* num_to_show;

  for (l = lst, i = 1; l != NULL; l = l->next, i++)
  {
    num_to_show = l->data;
    g_print("Num [%ld] : %s\n", i, num_to_show);
  }
}

void aff_contact(Contact_t *un_mec)
{
  g_print("\n/******************************/\n");
  if (un_mec->Name)
  {
    g_print("Nom : %s \n", un_mec->Name);
  }
  if (un_mec->Prenom)
  {
    g_print("Prenom : %s \n", un_mec->Prenom);
  }

  if (un_mec->Email)
  {
    g_print("Email : %s \n", un_mec->Email);
  }

  if (un_mec->Anniv)
  {
    g_print("Anniv : %s \n", un_mec->Anniv);
  }

  show_num(un_mec->Numero);

  if (un_mec->Adresse)
  {
    g_print("Adresse : %s \n", un_mec->Adresse);
  }

  if (un_mec->Notes)
  {
    g_print("Notes : %s \n", un_mec->Notes);
  }
}
//! Bug a cause de g_io_read line
void remove_end_of_line(gchar *s){ 
  gint i;
  for (i =0;s[i] != '\0';i++){

  }
  s[i] = ' ';
  s[i-1] = '\0';
}


void Crea_contact()
{
  GIOChannel *bref = g_io_channel_unix_new(0);
  GList *contact_data = NULL;
  gchar *entree;
  gint64 val;
  g_print("/*************************/\n");
  g_print("Nom :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  g_print("Prenom :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  g_print("Email :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  g_print("Combien de numero voulez-vous ajouter :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  val = g_ascii_strtoll(entree, NULL, 10);

  //Création de Glist UnType->Numero
  for (gint64 i = 0; i < val; i++)
  {
    g_print("Numero %ld :", i + 1);
    g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
    remove_end_of_line(entree);
    contact_data = g_list_append(contact_data, g_strdup(entree));
  }

  g_print("Anniv :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  g_print("Adresse :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  g_print("Notes :");
  g_io_channel_read_line(bref, &entree, NULL, NULL, NULL);
  remove_end_of_line(entree);
  contact_data = g_list_append(contact_data, g_strdup(entree));

  init_contact(contact_data);
}

void voir_list_contact_detailler()
{
  GList *L = list_contact_sorted();
  Contact_t *Encours_affiche;
  const gchar *espace = " ";
  for (GList *elem = L; elem != NULL; elem = elem->next)
  {
    //TODO A changer moche
    lookup_Contact(elem->data);
    Encours_affiche = current_contact();
    aff_contact(Encours_affiche);
  }
}

void voir_list_rapide()
{
  GList *L = list_contact_sorted();
  gchar *Encours_affiche;
  for (gint64 i = 1; L != NULL; L = L->next, i++)
  {
    Encours_affiche = L->data;
    g_print("Contact %ld:\n %s", i, Encours_affiche);
  }
}

void menu()
{
  global_list_init("");
  gint64 choix = 0;
  while (choix != 9)
  {
    g_print("\nBienvenue Dans le Menu\n");
    g_print("1: Ajouter un Contact\n2: Afficher les contacts un par un\n3: Voir liste Rapide\nX: Quitter le Programme\n");
    g_print("Veuiller choisir une option :");
    GIOChannel *channel = g_io_channel_unix_new(0);
    gchar *input;
    g_io_channel_read_line(channel, &input, NULL, NULL, NULL);
    gint64 choix = g_ascii_strtoll(input, NULL, 10);
    switch (choix)
    {
    case 1:
      Crea_contact();
      break;
    case 2:
      voir_list_contact_detailler();
      break;
    case 3:
      voir_list_rapide();
      break;
      //TODO Faire le reste des options
    default:
      exit(0);
    }
  }
}

int main()
{
  menu();
}
