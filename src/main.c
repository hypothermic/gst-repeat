#include <gst/gst.h>

#include "error.h"
#include "log.h"

/**
 * The GStreamer pipeline description to parse.
 */
static gchar* pipeline_description = NULL;

/**
 * Whether to only construct the pipeline once and re-use it on every cycle.
 */
static gboolean pipeline_reuse = FALSE;

/**
 * A restriction on how many cycles can be executed.
 */
static gint   max_cycles           = 0;

/**
 * The amount of microseconds to sleep after a cycle has completed.
 */
static gint   sleep_after_cycle    = 5000000;

/**
 * The command-line option entries which will be parsed.
 */
static GOptionEntry option_entries[] = {
        {"pipeline",   'p', 0, G_OPTION_ARG_STRING, &pipeline_description, "Pipeline description to parse",                   NULL},
        {"reuse",      'r', 0, G_OPTION_ARG_NONE,   &pipeline_reuse,       "Only parse the pipeline once and re-use it",      NULL},
        {"max-cycles", 'c', 0, G_OPTION_ARG_INT,    &max_cycles,           "How many times to repeat (0 for indefinite)",     "N" },
        {"sleep",      's', 0, G_OPTION_ARG_INT,    &sleep_after_cycle,    "How long to sleep between cycles (microseconds)", "MS"},
        {NULL}
};

/**
 * Entry point
 */
int main(int argc, char **argv) {
    GError *error = NULL;
    GOptionContext *context;

    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    gst_init(NULL, NULL);
    gst_debug_set_active(TRUE);
    gst_debug_category_set_threshold(GST_CAT_DEFAULT, GST_LEVEL_WARNING);

    INFO(R_DEPTH_ROUTINE, "Initialized gst-repeat v%s", R_VERSION);

    /* Parse options */
    context = g_option_context_new("- gst-repeat options");
    g_option_context_add_main_entries(context, option_entries, NULL);
    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        ERROR(R_DEPTH_ROUTINE, "option parsing failed: %s\n", error->message);
        return R_CODE_ERROR_OPTIONS;
    }
    if (pipeline_description == NULL) {
        ERROR(R_DEPTH_ROUTINE, "pipeline description must be specified! (-p)");
        return R_CODE_ERROR_NO_PIPELINE;
    }

    INFO(R_DEPTH_ROUTINE, "Repeating until %d cycles have passed", max_cycles);

    /* Repeat as long as we're under max_repeats */
    int cycle_count = 0;
    while (max_cycles == 0 || cycle_count < max_cycles) {
        cycle_count++;
        INFO(R_DEPTH_ACTION, "Running cycle %d", cycle_count);

        /* Parse pipeline */
        pipeline = gst_parse_launch(pipeline_description, NULL);

        /* Start playing */
        gst_element_set_state(pipeline, GST_STATE_PLAYING);

        /* Wait until error or EOS */
        bus = gst_element_get_bus(pipeline);
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

        /* Free resources */
        if (msg != NULL)
            gst_message_unref(msg);
        gst_object_unref(bus);

        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);

        /* Sleep until next cycle */
        g_usleep(sleep_after_cycle);
    }

    INFO(R_DEPTH_ROUTINE, "Gracefully exiting after %d cycles", cycle_count);

    return R_CODE_SUCCESS;
}