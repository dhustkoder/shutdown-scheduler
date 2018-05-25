#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static const char *hours = "00", *minutes = "00";

void time_change(GtkComboBoxText* widget, gpointer user_data)
{
	const char* str = ((void*)user_data);
	printf("USERDATA: %s\n", str);

	if (strcmp(str, "hours") == 0) {
		hours = gtk_combo_box_text_get_active_text(widget);
	} else {
		minutes = gtk_combo_box_text_get_active_text(widget);
	}

	printf("%s:%s\n", hours, minutes);
}

void switch_set(GtkSwitch *widget, gboolean state, gpointer user_data)
{
	if (state) {
		printf("ON\n");
	} else {
		printf("OFF\n");
	}
}

int main (int argc, char *argv[])
{
	GtkBuilder *builder;
	GObject *window, *hours, *minutes, *switchh;
	GError *error = NULL;

	gtk_init(&argc, &argv);

	/* Construct a GtkBuilder instance and load our UI description */
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file(builder, "layout.glade", &error) == 0) {
		g_printerr("Error loading file: %s\n", error->message);
		g_clear_error(&error);
		return 1;
	}

	/* Connect signal handlers to the constructed widgets. */
	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	hours = gtk_builder_get_object(builder, "hours");
	g_signal_connect(hours, "changed", G_CALLBACK(time_change), "hours");

	minutes = gtk_builder_get_object(builder, "minutes");
	g_signal_connect(minutes, "changed", G_CALLBACK(time_change), "minutes");

	switchh = gtk_builder_get_object(builder, "switch");
	g_signal_connect(switchh, "state-set", G_CALLBACK(switch_set), NULL);


	gtk_main();
	
	return 0;
}