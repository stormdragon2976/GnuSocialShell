/*
 * Copyright (C) 2016 Dan Rulos.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <curl/curl.h>
#include "gnusocial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_status(struct gss_account account, char *msg)
{
	char url[100];
	sprintf(url, "%s://%s/api/statuses/update.xml", account.protocol, account.server);

	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
	curl_easy_setopt(curl, CURLOPT_USERNAME, account.user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, account.password);
	char *buffer = malloc((31+strlen(msg)));
	sprintf(buffer, "source=GnuSocialShell&status=%s", msg);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	char *xml_data = (char *)malloc(filesize);
	fread(xml_data, filesize, filesize, xml);
	fclose(xml);
	int xml_data_size = strlen(xml_data);
	char *error = (char *)malloc(512);
	if (parseXml(xml_data, xml_data_size, "<error>", 7, error, 512) > 0) {
		printf("Error: %s\n", error);
	}
	free(error);
	free(xml_data);
	free(buffer);
}
