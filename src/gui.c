#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define TEXT_SURFACE_SIZE 100
#define TEXT_BASE 32.0
#define PADDING 1.0

// TODO: correct indent

static gboolean update_entry (char *str);

void gui_set(char *str)
{
   // TODO: check!!
   char *str_copy = (char *) malloc (sizeof (char) * 20);
   strcpy(str_copy, str);
   gdk_threads_add_idle ((GSourceFunc) update_entry, str_copy);
}

static GdkPixbuf* getPixBuf (const char *utf8)
{
	// Preprare Cairo objects.
	cairo_surface_t *surface = cairo_image_surface_create (
		CAIRO_FORMAT_ARGB32, TEXT_SURFACE_SIZE, TEXT_SURFACE_SIZE);
	g_assert (surface != NULL);
	cairo_t *cr = cairo_create (surface);
	g_assert (cr != NULL);

	// Clean surface.
	cairo_set_source_rgba (cr, 0, 0, 0, 0);
	cairo_paint (cr);

	// Paint the text.
	cairo_select_font_face (
		cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, TEXT_BASE);
	cairo_move_to (cr, TEXT_BASE, TEXT_BASE);
	cairo_set_source_rgba (cr, 0.0, 1.0, 1.0, 1.0);
	cairo_show_text (cr, utf8);

	// Get sizes.
	cairo_text_extents_t extends;
	cairo_text_extents (cr, utf8, &extends);

	// Debug output.
	//printf("ex: %f %f %f %f", extends.width, extends.height,
	//		extends.x_bearing, extends.y_bearing);

	// Get pixbuf from surface.
	double x = (TEXT_BASE - PADDING) + extends.x_bearing;
	double y = (TEXT_BASE - PADDING) + extends.y_bearing;
	double w = extends.width + (2 * PADDING);
	double h = extends.height + (2 * PADDING);

	// TODO: Crop surface to size of trace icon?

	// Output must be a rectangle, we do not want to scale anything.
	// So take the larger dimension, the other one move to center.
	double fs = MAX(w, h); // Final size.
	GdkPixbuf *pixbuf = gdk_pixbuf_get_from_surface (
		surface, (x-(fs-w)/2), (y-(fs-h)/2), fs, fs);

	// Clean up Cairo objects.
	cairo_surface_destroy (surface);
	cairo_destroy (cr);

	return pixbuf;
}


// In initialized in "active" function.
GtkStatusIcon *tray_icon;

static gboolean update_entry (char *str)
{
	GdkPixbuf *pixbufout = getPixBuf (str);
	gtk_status_icon_set_from_pixbuf (tray_icon, pixbufout);

	free(str);

	return G_SOURCE_REMOVE;
}


static void updateTray (gpointer user_data)
{
	// TODO: buffer size
	while (1) {
		char *str = (char *) malloc (sizeof (char) * 20);
		scanf("%s", str);
		gdk_threads_add_idle ((GSourceFunc) update_entry, str);
	}
}

static void activate (GtkApplication* app, gpointer user_data)
{
   // TODO: zkouknout jeste

   GtkWidget *window;

   window = gtk_application_window_new (app);
   gtk_window_set_title (GTK_WINDOW (window), "Welcome to GNOME");
   gtk_window_set_default_size (GTK_WINDOW (window), 100, 100);

   GdkPixbuf *pixbufout = getPixBuf ("BLE");
   GtkWidget *pb = gtk_image_new_from_pixbuf (pixbufout);
   gtk_container_add (GTK_CONTAINER (window), pb);

   // Show status icon.
   tray_icon = gtk_status_icon_new ();
   gtk_status_icon_set_from_pixbuf (tray_icon, pixbufout);
   gtk_status_icon_set_visible (tray_icon, TRUE);

   //gtk_widget_show_all (window);
}

GtkApplication *app;

void gui_init()
{

	app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);

	//g_thread_new ("dummy", (GThreadFunc)updateTray, NULL);


	//return status;
}

void gui_start()
{
	g_application_run (G_APPLICATION (app), 0, NULL);
	g_object_unref (app);
}


