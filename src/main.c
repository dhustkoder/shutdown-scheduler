#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>


static const char *hours = "00";
static const char *minutes = "00";
static bool switch_state = false;


static void cancel_shutdown_timer()
{
	printf("OFF\n");
	system("shutdown -c");
}

static void setup_shutdown_timer()
{
	static char buffer[64];
	printf("ON\n");
	sprintf(buffer, "shutdown -h %s:%s", hours, minutes);
	system(buffer);

}

static void time_change(GtkComboBoxText* const widget, const gpointer user_data)
{
	const char* const str = ((void* const)user_data);
	printf("USERDATA: %s\n", str);

	if (strcmp(str, "hours") == 0) {
		hours = gtk_combo_box_text_get_active_text(widget);
	} else {
		minutes = gtk_combo_box_text_get_active_text(widget);
	}

	if (switch_state) {
		cancel_shutdown_timer();
		setup_shutdown_timer();
	}

	printf("%s:%s\n", hours, minutes);
}

static void switch_set(GtkSwitch* const widget, const gboolean state, const gpointer user_data)
{
	switch_state = state;
	if (switch_state)
		setup_shutdown_timer();
	else
		cancel_shutdown_timer();
}



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkBuilder* const builder = gtk_builder_new();
	GError *error = NULL;
	if (gtk_builder_add_from_file(builder, "layout.glade", &error) == 0) {
		g_printerr("Error loading file: %s\n", error->message);
		g_clear_error(&error);
		return 1;
	}

	/* Connect signal handlers to the constructed widgets. */
	GObject* const window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GObject* const hours_cb = gtk_builder_get_object(builder, "hours");
	g_signal_connect(hours_cb, "changed", G_CALLBACK(time_change), "hours");

	GObject* const minutes_cb = gtk_builder_get_object(builder, "minutes");
	g_signal_connect(minutes_cb, "changed", G_CALLBACK(time_change), "minutes");

	GObject* const switch_obj = gtk_builder_get_object(builder, "switch");
	g_signal_connect(switch_obj, "state-set", G_CALLBACK(switch_set), NULL);


	gtk_main();

	if (switch_state)
		cancel_shutdown_timer();
	
	return 0;
}
