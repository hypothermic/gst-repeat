# gst-repeat

A simple application to repeat gst-launch without parsing the pipeline every time.

## Options

These can be specified as command-line arguments to adjust gst-repeat's behaviour.

| Short Name |  Long Name   | Default Value |           Description           |
| ---------- | ------------ | ------------- | ------------------------------- |
| -p         | --pipeline   | _none_        | A gstreamer pipeline to parse   |
| -r         | --reuse      | false         | Whether to reuse the pipeline element instead of parsing it on every cycle. |
| -c         | --max-cycles | 0             | The amount of times to repeat.  |
| -s         | --sleep      | 5 seconds     | The amount of microseconds to sleep after completing a cycle. |

## Example

Repeat the "Hello World" tutorial from GStreamer's website exactly four times with no sleep time:

```sh
gst-repeat -c 4 -s 0 -p "playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"
```