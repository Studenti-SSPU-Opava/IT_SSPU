function detectRepo() {
	const host = window.location.hostname;
	const path = window.location.pathname;
	if (!host.endsWith('github.io')) return null;

	const owner = host.split('.')[0];
	const name = path.split('/').filter(Boolean)[0];
	if (!owner || !name) return null;

	return { owner, name };
}

const REPO = detectRepo() || { owner: 'Studenti-SSPU-Opava', name: 'IT_SSPU' };

const repoUrl = `https://github.com/${REPO.owner}/${REPO.name}`;
document.getElementById('repo-link')?.setAttribute('href', repoUrl);
document.getElementById('wiki-link')?.setAttribute('href', repoUrl + '/wiki');

function escapeHtml(str) {
	return str.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}

function dirPathOf(filePath) {
	const idx = filePath.lastIndexOf('/');
	return idx === -1 ? '' : filePath.slice(0, idx);
}

function isImage(filePath) {
	return /\.(png|jpe?g|gif|svg|webp|bmp|ico)$/i.test(filePath);
}

function isHtml(filePath) {
	return /\.html?$/i.test(filePath);
}

function isAbsoluteUrl(val) {
	return /^(?:[a-z][a-z0-9+.-]*:|\/\/|\/|#|data:)/i.test(val);
}

function stripLiquidRaw(html) {
	return html.replace(/\{%\s*raw\s*%\}|\{%\s*endraw\s*%\}/gi, '');
}

function fixRelativeLinks(html, baseDir) {
	const wrapper = document.createElement('div');
	wrapper.innerHTML = html;

	for (const el of wrapper.querySelectorAll('img[src], a[href]')) {
		const attr = el.tagName === 'IMG' ? 'src' : 'href';
		const val = el.getAttribute(attr);
		if (!val || isAbsoluteUrl(val)) continue;

		const cleaned = val.replace(/^\.\//, '');
		el.setAttribute(attr, (baseDir ? baseDir + '/' : '') + cleaned);
	}

	return wrapper.innerHTML;
}

function iconFor(name) {
	if (name.endsWith('.md')) return '📝';
	if (name.endsWith('.html')) return '🌐';
	if (name.endsWith('.css')) return '🎨';
	if (name.endsWith('.js')) return '⚙️';
	if (name.endsWith('.py')) return '🐍';
	if (name.endsWith('.c')) return '🔧';
	if (name.endsWith('.pdf')) return '📄';
	if (isImage(name)) return '🖼️';
	return '📄';
}

async function listDir(path) {
	const cacheKey = 'dir:' + path;
	const cached = sessionStorage.getItem(cacheKey);
	if (cached) {
		try {
			return JSON.parse(cached);
		} catch (e) {}
	}

	const url = `https://api.github.com/repos/${REPO.owner}/${REPO.name}/contents${path ? '/' + encodeURIComponent(path) : ''}`;
	const res = await fetch(url, { headers: { Accept: 'application/vnd.github+json' } });

	if (res.status === 403) {
		throw new Error('GitHub si teď dal pauzu (vyčerpaný limit požadavků). Zkus to za pár minut.');
	}
	if (!res.ok) {
		throw new Error(`Soubor se nepodařilo stáhnout (kód ${res.status}).`);
	}

	const data = await res.json();
	sessionStorage.setItem(cacheKey, JSON.stringify(data));
	return data;
}

function buildBreadcrumb(path) {
	const parts = path ? path.split('/') : [];
	const crumb = document.createElement('nav');
	crumb.className = 'breadcrumb';

	const root = document.createElement('a');
	root.href = '#/';
	root.textContent = 'root';
	crumb.appendChild(root);

	let acc = '';
	for (const part of parts) {
		acc += (acc ? '/' : '') + part;
		const sep = document.createElement('span');
		sep.className = 'sep';
		sep.textContent = ' / ';
		crumb.appendChild(sep);

		const a = document.createElement('a');
		a.href = '#/' + acc + '/';
		a.textContent = part;
		crumb.appendChild(a);
	}
	return crumb;
}

async function showListing(viewer, path) {
	viewer.innerHTML = '';

	viewer.appendChild(buildBreadcrumb(path));

	const wrap = document.createElement('div');
	wrap.className = 'hint-wrap';

	const hint = document.createElement('p');
	hint.className = 'empty';
	hint.textContent = path
		? `Tohle je složka. Vyber si soubor ve stromu vlevo.`
		: 'Vyber si soubor ve stromu vlevo.';
	wrap.appendChild(hint);

	const openBtn = document.createElement('button');
	openBtn.type = 'button';
	openBtn.className = 'open-tree-btn';
	openBtn.textContent = '📁 Otevřít strom';
	openBtn.addEventListener('click', () => setSidebarVisible(true));
	wrap.appendChild(openBtn);

	viewer.appendChild(wrap);
}

function buildHtmlViewer(filePath, text) {
	const wrapper = document.createElement('div');
	wrapper.className = 'html-viewer';

	const toggle = document.createElement('div');
	toggle.className = 'view-toggle';

	const codeBtn = document.createElement('button');
	codeBtn.type = 'button';
	codeBtn.className = 'view-toggle-btn active';
	codeBtn.textContent = 'Kód';
	codeBtn.dataset.view = 'code';

	const previewBtn = document.createElement('button');
	previewBtn.type = 'button';
	previewBtn.className = 'view-toggle-btn';
	previewBtn.textContent = 'Náhled';
	previewBtn.dataset.view = 'preview';

	toggle.appendChild(codeBtn);
	toggle.appendChild(previewBtn);

	const openTab = document.createElement('a');
	openTab.className = 'open-tab';
	openTab.href = filePath;
	openTab.target = '_blank';
	openTab.rel = 'noopener';
	openTab.textContent = 'Otevřít v nové kartě';

	const bar = document.createElement('div');
	bar.className = 'view-bar';
	bar.appendChild(toggle);
	bar.appendChild(openTab);
	wrapper.appendChild(bar);

	const codeView = document.createElement('pre');
	codeView.className = 'view-pane code';
	const code = document.createElement('code');
	code.textContent = text;
	codeView.appendChild(code);
	wrapper.appendChild(codeView);

	const previewView = document.createElement('div');
	previewView.className = 'view-pane preview';
	previewView.hidden = true;
	const frame = document.createElement('iframe');
	frame.src = filePath;
	frame.title = fileNameFor(frame.src);
	previewView.appendChild(frame);
	wrapper.appendChild(previewView);

	toggle.addEventListener('click', (e) => {
		const btn = e.target.closest('.view-toggle-btn');
		if (!btn) return;

		for (const b of toggle.querySelectorAll('.view-toggle-btn')) {
			b.classList.toggle('active', b === btn);
		}

		codeView.hidden = btn.dataset.view !== 'code';
		previewView.hidden = btn.dataset.view !== 'preview';
	});

	return wrapper;
}

function fileNameFor(path) {
	return decodeURIComponent(path.split('/').pop());
}

async function fetchFile(filePath) {
	const res = await fetch(filePath);
	if (res.ok) return res.text();

	if (res.status === 404) {
		const raw = `https://raw.githubusercontent.com/${REPO.owner}/${REPO.name}/main/${filePath}`;
		const rawRes = await fetch(raw);
		if (rawRes.ok) return rawRes.text();
		throw new Error(`Soubor se nepodařilo stáhnout (kód ${rawRes.status}).`);
	}

	throw new Error(`Soubor se nepodařilo stáhnout (kód ${res.status}).`);
}

async function showFile(viewer, filePath) {
	viewer.innerHTML = '<p class="loading">Moment, otevírám soubor…</p>';

	try {
		const text = await fetchFile(filePath);
		viewer.innerHTML = '';

		const fileName = decodeURIComponent(filePath.split('/').pop());
		const parentDir = dirPathOf(filePath);

		viewer.appendChild(buildBreadcrumb(parentDir));

		const heading = document.createElement('h2');
		heading.className = 'page-title';
		heading.textContent = fileName;
		viewer.appendChild(heading);

		const card = document.createElement('div');
		card.className = 'card';

		if (isImage(filePath)) {
			const img = document.createElement('img');
			img.src = filePath;
			img.alt = fileName;
			card.appendChild(img);
		} else if (filePath.endsWith('.md')) {
			card.innerHTML = fixRelativeLinks(stripLiquidRaw(marked.parse(text)), parentDir);
		} else if (isHtml(filePath)) {
			card.appendChild(buildHtmlViewer(filePath, text));
		} else {
			const pre = document.createElement('pre');
			const code = document.createElement('code');
			code.textContent = text;
			pre.appendChild(code);
			card.appendChild(pre);
		}

		viewer.appendChild(card);
	} catch (error) {
		console.log(error);
		viewer.innerHTML = `<div class="error"><h1>Tenhle soubor tu není</h1><p>Nepovedlo se ho načíst: <code>${escapeHtml(filePath)}</code></p></div>`;
	}
}

async function handleRoute() {
	const viewer = document.getElementById('viewer');

	const hash = window.location.hash;

	if (!hash || hash === '#/') {
		await showListing(viewer, '');
		return;
	}

	const filePath = hash.replace(/^#\/?/, '');

	if (filePath.endsWith('/')) {
		await showListing(viewer, filePath.replace(/\/$/, ''));
		return;
	}

	await showFile(viewer, filePath);
}

window.addEventListener('hashchange', handleRoute);
window.addEventListener('DOMContentLoaded', handleRoute);

// ---- Sidebar (VSCode-style file tree) ----

let sidebarEl;

let sidebarOpen = true;

function setSidebarVisible(visible) {
	sidebarOpen = visible;
	document.body.classList.toggle('sidebar-visible', sidebarOpen);
	const toggle = document.getElementById('sidebar-toggle');
	toggle.setAttribute('aria-expanded', sidebarOpen ? 'true' : 'false');
	// Backdrop only shows on mobile while the sidebar drawer is open.
	document.getElementById('backdrop').hidden = !(window.innerWidth <= 820 && sidebarOpen);
}

function attachTreeEvents() {
	const toggle = document.getElementById('sidebar-toggle');
	const backdrop = document.getElementById('backdrop');

	const onResize = () => setSidebarVisible(sidebarOpen);
	window.addEventListener('resize', onResize);

	toggle.addEventListener('click', () => setSidebarVisible(!sidebarOpen));
	backdrop.addEventListener('click', () => setSidebarVisible(false));
	document.getElementById('sidebar-close').addEventListener('click', () => setSidebarVisible(false));
}

function makeSidebarResizable() {
	const sidebar = document.getElementById('sidebar');
	const resizer = document.getElementById('sidebar-resizer');
	const isMobile = () => window.innerWidth <= 820;
	const clamp = (v, min, max) => Math.max(min, Math.min(v, max));

	// Restore saved width.
	const saved = localStorage.getItem('tree-width');
	if (saved) sidebar.style.width = saved + 'px';

	resizer.addEventListener('pointerdown', (e) => {
		if (isMobile()) return;
		e.preventDefault();
		document.body.classList.add('resizing');
		document.addEventListener('pointermove', onMove);
		document.addEventListener('pointerup', onUp);
	});

	function onMove(e) {
		const rect = sidebar.getBoundingClientRect();
		const w = clamp(e.clientX - rect.left, 180, Math.min(640, window.innerWidth * 0.45));
		sidebar.style.width = w + 'px';
		localStorage.setItem('tree-width', w);
	}

	function onUp() {
		document.body.classList.remove('resizing');
		document.removeEventListener('pointermove', onMove);
		document.removeEventListener('pointerup', onUp);
	}
}

function buildTreeItem(entry) {
	const isDir = entry.type === 'dir';
	const row = document.createElement('div');
	row.className = 'tree-item ' + (isDir ? 'dir' : 'file');
	row.dataset.kind = isDir ? 'dir' : 'file';
	row.dataset.name = entry.name;
	row.dataset.path = entry.path;

	const caret = document.createElement('span');
	caret.className = 'caret';
	caret.textContent = isDir ? '▸' : '';
	row.appendChild(caret);

	const icon = document.createElement('span');
	icon.className = 'entry-icon';
	icon.textContent = isDir ? '📁' : iconFor(entry.name);
	row.appendChild(icon);

	const name = document.createElement('span');
	name.className = 'entry-name';
	name.textContent = entry.name;
	row.appendChild(name);

	if (isDir) {
		row.addEventListener('click', () => toggleDir(row, entry.path));
	} else {
		row.addEventListener('click', () => {
			window.location.hash = '#/' + entry.path;
		});
	}
	return row;
}

async function expandDir(row, path) {
	if (row.classList.contains('loaded')) {
		row.classList.add('open');
		if (row._children) row._children.hidden = false;
		return;
	}

	row.classList.add('open', 'loaded');
	const children = document.createElement('div');
	children.className = 'tree-children';
	children.style.paddingLeft = '0.9rem';
	row._children = children;
	row.after(children);

	try {
		const entries = await listDir(path);
		children.append(...entries.map(buildTreeItem));
	} catch (e) {
		children.remove();
		row.classList.remove('open', 'loaded');
	}
}

function collapseDir(row) {
	row.classList.remove('open');
	if (row._children) row._children.hidden = true;
}

function toggleDir(row, path) {
	if (row.classList.contains('open')) collapseDir(row);
	else expandDir(row, path);
}

function findTreeItem(el, name) {
	const items = el.querySelectorAll(':scope > .tree-item');
	for (const it of items) if (it.dataset.name === name) return it;
	return null;
}

async function revealPath(path) {
	sidebarEl.querySelectorAll('.tree-item.active').forEach(n => n.classList.remove('active'));
	if (!path) return;

	const parts = path.split('/');
	let container = sidebarEl.querySelector('.tree-root');
	let acc = '';

	for (let i = 0; i < parts.length; i++) {
		const isLast = i === parts.length - 1;
		acc += (acc ? '/' : '') + parts[i];
		const row = findTreeItem(container, parts[i]);
		if (!row) break;

		if (row.dataset.kind === 'dir') {
			if (!row.classList.contains('loaded')) {
				await expandDir(row, acc);
			} else {
				row.classList.add('open');
				if (row._children) row._children.hidden = false;
			}
			if (isLast) row.classList.add('active');
			container = row._children;
		} else {
			if (isLast) row.classList.add('active');
			break;
		}
	}
}

function updateActive() {
	const hash = window.location.hash;
	const filePath = hash ? hash.replace(/^#\/?/, '') : '';
	revealPath(filePath.replace(/\/$/, ''));
}

async function initTree() {
	sidebarEl = document.getElementById('sidebar');
	attachTreeEvents();
	setSidebarVisible(window.innerWidth > 820);
	makeSidebarResizable();

	const root = sidebarEl.querySelector('.tree-root');
	const container = document.createElement('div');
	container.className = 'tree-children';
	root.appendChild(container);

	try {
		const entries = await listDir('');
		container.append(...entries.map(buildTreeItem));
	} catch (e) {}

	updateActive();
	window.addEventListener('hashchange', updateActive);
}

window.addEventListener('DOMContentLoaded', initTree);
