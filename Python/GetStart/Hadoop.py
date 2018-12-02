#! python3

import requests, bs4, os

url = "http://xkcd.com"
os.makedirs('xkcd',exist_ok = True)
while not url.endswith('#'):

	# download the page
	print('downloading the %s' % url)
	res = requests.get(url)
	res.raise_for_status()
	soup = bs4.BeautifulSoup(res.text)

	# find the URL of the comic image
	comicElem = soup.select('#comic image')
	if comicElem == []:
		print('Couldn not find the iamge')
	else:
		comicUrl = comicElem[0].get('src')

		# download the image
		print('Downloading the image')
		res = requests.get(comicUrl)
		res.raise_for_status()

		# TODO: Save the iamge to ./xkcd.
		imagefile = open(os.path.join('xkcd', os.path.basename(comicUrl)), 'wb')
		for chunk in res.iter_content(100000):
			imagefile.write(chunk)
		imagefile.close()

	# TODO: Get the Prev button;s url
	prevlink = soup.select('a[rel="prev"]')[0]
	url = 'heep://xkcd.com' + prevlink.get('href')

print('Done...')





