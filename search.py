
import os


def read_tag(path):
	tags = {}
	with open(path, 'r', encoding='utf-8') as file:
		tag_begin = False
		for line in file.readlines():
			if line.startswith('**/'):
				tag_begin = False
			if tag_begin:
				if ':' not in line:
					tag_begin = False
					break
				if line.startswith('*'):
					line = line[1:]
					key, val = line.split(':')
					tags[key.strip()] = val.strip()
			if line.startswith('/**'):
				tag_begin = True
	return tags


if __name__ == '__main__':
	for root, dirname, files in os.walk('.'):
		if '.vscode' in root or '.git' in root:
			continue
		for filename in files:
			if not filename.endswith('.cpp'):
				continue
			tags = read_tag(os.path.join(root, filename))
			if tags and '上下界' in tags['Tag']:
				print(tags)