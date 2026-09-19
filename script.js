document.getElementById('year').textContent = new Date().getFullYear();

const navToggle = document.getElementById('navToggle');
const navLinks = document.getElementById('navLinks');

navToggle.addEventListener('click', () => {
  const isOpen = navLinks.classList.toggle('open');
  navToggle.setAttribute('aria-expanded', String(isOpen));
});

navLinks.querySelectorAll('a').forEach(link => {
  link.addEventListener('click', () => {
    navLinks.classList.remove('open');
    navToggle.setAttribute('aria-expanded', 'false');
  });
});

/* ── Source code viewer modal ── */
const codeModal = document.getElementById('codeModal');
const codeModalTitle = document.getElementById('codeModalTitle');
const codeModalCode = document.getElementById('codeModalCode');
const codeCache = {};

async function openCodeModal(src, title) {
  codeModalTitle.textContent = title || src;
  codeModalCode.textContent = 'Loading…';
  codeModal.hidden = false;
  document.body.style.overflow = 'hidden';
  try {
    if (!codeCache[src]) {
      const res = await fetch(src);
      if (!res.ok) throw new Error('Failed to load source');
      codeCache[src] = await res.text();
    }
    codeModalCode.textContent = codeCache[src];
  } catch (err) {
    codeModalCode.textContent = 'Could not load source file.';
  }
}

function closeCodeModal() {
  codeModal.hidden = true;
  document.body.style.overflow = '';
}

document.querySelectorAll('[data-view-src]').forEach(btn => {
  btn.addEventListener('click', () => {
    openCodeModal(btn.getAttribute('data-view-src'), btn.getAttribute('data-title'));
  });
});

document.getElementById('codeModalBackdrop').addEventListener('click', closeCodeModal);
document.getElementById('codeModalClose').addEventListener('click', closeCodeModal);
document.addEventListener('keydown', (e) => {
  if (e.key === 'Escape' && !codeModal.hidden) closeCodeModal();
});
