#Ubuntu 16.04.3 Server Setup

These docs target Ubuntu 6.04 on DigitalOcean.com and Kubuntu 16.04.3 where I do my home development. 

[Install LAMP](https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-16-04k)

[Install phpmyadmin](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-16-04)

Everything installed for me except putting phpmyadmin.conf into the apache config directory /etc/apache2/conf-available/. I had to manually do that and restart apache. [See this note about it](https://stackoverflow.com/questions/26891721/phpmyadmin-not-found-after-install-on-apache-ubuntu).

```bash
sudo ln -s /etc/phpmyadmin/apache.conf` /etc/apache2/conf-available/phpmyadmin.conf
sudo a2enconf phpmyadmin.conf
sudo systemctl restart apache2
```

Install C++
```bash
sudo apt-get install build-essential
```

Install Boost Libraries
```bash
sudo apt install libboost-all-dev
```

Install MySQL Client Dev
```bash
sudo apt install libmysqlclient-dev
```

##Install Poco Libraries
<p style="color:red;">
To be added later
</p>

Finally if make is not finding the libraries, you may need to run `ldconfig`.
```bash
sudo -i
cd /usr/local/lib
ldconfig
```

##Useful Commands

```bash
sudo systemctl stop apache2
sudo systemctl start apache2
sudo systemctl restart apache2
sudo systemctl reload apache2

```