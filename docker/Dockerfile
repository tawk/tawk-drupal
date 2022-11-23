ARG DRUPAL_IMAGE_VERSION

FROM drupal:${DRUPAL_IMAGE_VERSION}

COPY --chown=www-data:www-data ./bin/tawkto /var/www/html/modules/tawkto

WORKDIR /var/www/html

CMD ["apache2-foreground"]
