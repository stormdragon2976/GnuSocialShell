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

#include "gnusocial.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account_info get_my_account_info(struct gss_account account)
{
	char url[100];
	sprintf(url, "%s://%s/api/users/show.xml&screen_name=%s", account.protocol, account.server, account.user);
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, account.user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, account.password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
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
	char *error = (char *)malloc(512);
	char *output = (char *)malloc(512);
	int xml_data_size = strlen(xml_data);
	struct account_info info;
	if (parseXml(xml_data, xml_data_size, "<error>", 7, error, 512) > 0) {
		printf("Error: %s\n", error);
	}
	else {
		if (parseXml(xml_data, xml_data_size, "<name>", 6, output, 512) > 0) {
			strcpy(info.name, output);
		}
		else {
			info.name[0] = '?';
			info.name[1] = '\0';
		}
		if (parseXml(xml_data, xml_data_size, "<screen_name>", 13, output, 512) > 0) {
			strcpy(info.screen_name, output);
		}
		else {
			info.name[0] = '?';
			info.name[1] = '\0';
		}
		if (parseXml(xml_data, xml_data_size, "<location>", 10, output, 512) > 0) {
			strcpy(info.location, output);
		}
		else {
			info.name[0] = '?';
			info.name[1] = '\0';
		}
		if (parseXml(xml_data, xml_data_size, "<description>", 13, output, 512) > 0) {
			strcpy(info.description, output);
		}
		else {
			info.name[0] = '?';
			info.name[1] = '\0';
		}
		if (parseXml(xml_data, xml_data_size, "<url>", 5, output, 512) > 0) {
			strcpy(info.url, output);
		}
		else {
			info.name[0] = '?';
			info.name[1] = '\0';
		}
		if (parseXml(xml_data, xml_data_size, "<followers_count>", 17, output, 512) > 0) {
			info.followers = atoi(output);
		}
		else {
			info.followers = -1;
		}
		if (parseXml(xml_data, xml_data_size, "<friends_count>", 15, output, 512) > 0) {
			info.friends = atoi(output);
		}
		else {
			info.friends = -1;
		}
		if (parseXml(xml_data, xml_data_size, "<statuses_count>", 16, output, 512) > 0) {
			info.statuses = atoi(output);
		}
		else {
			info.statuses = -1;
		}
	}
	free(output);
	free(error);
	free(xml_data);
	return info;
}
