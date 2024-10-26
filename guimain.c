#include <sys/stat.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;

char *load_file(char *filename) {
	FILE *f;
	f = fopen(filename, "r");

    if (f == NULL) {
		exit(1);
    }
	// from: https://www.techiedelight.com/es/find-size-of-file-c/
    struct stat st;
    stat(filename, &st);
    off_t size = st.st_size;

	char c;
	int capacidad = size;
	char *vector = NULL;
    vector = (char *)malloc((capacidad + 1)* sizeof(char));// reserva capacidad*sizeof(char) 8 en memoria
	if(vector==NULL){
		fclose(f);
		exit(1);
	}
    while ((c = fgetc(f)) != EOF) {
		vector[count++] = c;
    }
	vector[count]='\0';
	fclose(f);
	return vector;
};

// Función para mostrar la matriz


void display_matrix(GtkWidget *grid, const char *vector, int filas, int columnas) {
    int pos = 0;
    int row = 0;
    int col = 0;

    while (pos < count) {
        char str[2] = { vector[pos], '\0' };  
        GtkWidget *label = gtk_label_new(str);
        GtkWidget *frame = gtk_frame_new(NULL);
        gtk_container_add(GTK_CONTAINER(frame), label);

        gtk_grid_attach(GTK_GRID(grid), frame, col, row, 1, 1);  

        if (vector[pos] == '\n') {
            row++;  
            col = 0;
        } else {
            col++; 
        }

        pos++;
    }

    gtk_widget_show_all(grid);
}

// Función de callback para el botón
void on_open_file(GtkWidget *widget, gpointer grid) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_chooser_dialog_new("Abrir archivo", GTK_WINDOW(gtk_widget_get_toplevel(widget)), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        char *vector = load_file(filename);
        
        // Asumimos un tamaño arbitrario para la matriz, por ejemplo, 40 columnas
        int columnas = 40;
        int filas = (count + columnas - 1) / columnas; // Calculamos las filas necesarias
        
        // Limpiar la cuadrícula anterior
        GList *children = gtk_container_get_children(GTK_CONTAINER(grid));
        for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
            gtk_widget_destroy(GTK_WIDGET(iter->data));
        }
        g_list_free(children);
        
        // Mostrar el contenido del archivo como matriz
        display_matrix(grid, vector, filas, columnas);
        
        free(vector);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Crear ventana principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Visualizador de Archivos en Matriz");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear caja vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Crear cuadrícula
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE); // Asegura que todas las columnas tengan el mismo tamaño
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);    // Asegura que todas las filas tengan el mismo tamaño
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Crear botón de apertura de archivo
    GtkWidget *open_button = gtk_button_new_with_label("Abrir Archivo");
    g_signal_connect(open_button, "clicked", G_CALLBACK(on_open_file), grid);
    gtk_box_pack_start(GTK_BOX(vbox), open_button, FALSE, FALSE, 0);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Ejecutar la aplicación GTK
    gtk_main();

    return 0;
}

