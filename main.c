#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <time.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;
    sfColor negra = {0, 0, 0};
    sfTexture* sheet;
    sfSprite* sprites;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sheet = sfTexture_createFromFile("kinknew.png", NULL);
    if (!sheet)
        return 1;

    sprites = sfSprite_create();
    sfIntRect clip = {0, 0, 16, 16};
    sfSprite_setTexture(sprites, sheet, sfTrue);
    sfSprite_setTextureRect(sprites, clip);

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyDown))
        {
            sfVector2f deltas = {0, 1};
            sfSprite_move(sprites, deltas);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, negra);

        sfRenderWindow_drawSprite(window, sprites, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
        usleep(16666);
    }

    /* Cleanup resources */
    sfSprite_destroy(sprites);
    sfTexture_destroy(sheet);
    sfRenderWindow_destroy(window);

    return 0;
}
