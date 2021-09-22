Drupal 7
============
Docker containers for Drupal 7

## Information
- Drupal Versions: 7
- MySQL Version: 5.7

## Pre-Requisites
- install docker-compose [http://docs.docker.com/compose/install/](http://docs.docker.com/compose/install/)

## Usage
Start the container:
- ```docker-compose up```

Start the container in detach mode:
- ```docker-compose up -d```

Stop the container:
- ```docker-compose stop```

Destroy the container and start from scratch:
- ```docker-compose down```
- ```docker volume rm docker_db_data docker_web_data```

## Plugin setup
You can follow the instructions in [Drupal 7 Github Repo](https://github.com/tawk/tawk-drupal)
