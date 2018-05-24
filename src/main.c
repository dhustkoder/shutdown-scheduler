#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window, *hours, *minutes;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Shutdown Scheduler");
	gtk_window_set_default_size(GTK_WINDOW(window), 360, 240);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	hours = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(hours), "0", "FLA");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(hours), "1", "LOP");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(hours), "2", "SFT");
	gtk_combo_box_set_active (GTK_COMBO_BOX(hours), 0);
	gtk_container_add(GTK_CONTAINER(window), hours);

	gtk_widget_show_all(window);
}

int main(int argc, char** argv)
{
	GtkApplication* app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}