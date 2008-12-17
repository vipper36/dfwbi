(load-file "/usr/share/emacs/site-lisp/cedet/common/cedet.el")
(set-default-font "-adobe-courier-medium-r-normal--14-100-100-100-m-90-iso10646-1")
(set-language-environment 'Chinese-GB)
(set-keyboard-coding-system 'euc-cn)
(set-clipboard-coding-system 'euc-cn)
(set-terminal-coding-system 'euc-cn)
(set-buffer-file-coding-system 'euc-cn)
(set-selection-coding-system 'euc-cn)
(modify-coding-system-alist 'process "*" 'euc-cn)
(setq default-process-coding-system 
            '(euc-cn . euc-cn))
(setq-default pathname-coding-system 'euc-cn)

(require 'ecb)
(require 'ecb-autoloads)
(semantic-load-enable-code-helpers)
(require 'xcscope)
(require 'cedet)
(require 'plsql)
(require 'sqlplus)
;;(require 'tabbar)
;;(require 'ide-skel)
(setq gdb-many-windows t)
(desktop-load-default)
(desktop-read)
;;(partial-completion-mode)
;;(icomplete-mode)
;;(set-background-color "DarkSlateGray")
;;(set-foreground-color "Wheat")
;;(set-face-background 'modeline "lightgoldenrod2")
;;(set-face-foreground 'modeline "DarkSlateGray")
;;(set-cursor-color "Orchid")
;;(set-face-foreground 'font-lock-comment-face "Gray")
;;(set-face-foreground 'font-lock-string-face "Gold3")
;;(set-face-foreground 'font-lock-function-name-face "LightBlue")
;;(set-face-foreground 'font-lock-keyword-face "cyan1")
;;(set-face-foreground 'font-lock-type-face "Violet")
;;(set-face-foreground 'font-lock-builtin-face "Cyan")
;;(set-face-foreground 'font-lock-variable-name-face "Gold")
;;(set-face-foreground 'font-lock-constant-face "Magenta")
;;(set-face-foreground 'scroll-bar "Wheat")
;;(set-face-background 'scroll-bar "lightgoldenrod2")
;;(set-face-foreground 'tool-bar "Wheat")
;;(set-face-background 'tool-bar "lightgoldenrod2")
;;(set-face-foreground 'font-lock-builtin-face "Cyan")
;;(set-face-background 'default "LightCyan3")
(set-face-background 'default "Black")
(set-foreground-color "White")
(set-cursor-color "White")
(setq tab-width 8
indent-tabs-mode t
c-basic-offset 8)

(setq semanticdb-project-roots 
(list
(expand-file-name "/")))
(defun my-indent-or-complete ()
   (interactive)
   (if (looking-at "\\>")
         (hippie-expand nil)
       (indent-for-tab-command))
 )
(global-set-key [(control tab)] 'my-indent-or-complete)



(autoload 'senator-try-expand-semantic "senator")

(setq hippie-expand-try-functions-list
        '(
	  senator-try-expand-semantic
	  try-expand-dabbrev
	  try-expand-dabbrev-visible
	  try-expand-dabbrev-all-buffers
	  try-expand-dabbrev-from-kill
	  try-expand-list
	  try-expand-list-all-buffers
	  try-expand-line
        try-expand-line-all-buffers
        try-complete-file-name-partially
        try-complete-file-name
        try-expand-whole-kill
        )
)
(global-set-key [(control tab)] 'senator-complete-symbol);
;;(global-set-key [(control tab)] ' senator-completion-menu-popup)
;; (global-set-key [(control tab)] 'semantic-ia-complete-symbol-menu)
(add-hook 'c-mode-hook 'imenu-add-menubar-index)
(add-hook 'c++-mode-hook 'imenu-add-menubar-index)
;;(global-set-key [f4] 'ide-skel-proj-find-files-by-regexp)
;;(global-set-key [f5] 'ide-skel-proj-grep-files-by-regexp)
;;(global-set-key [f10] 'ide-skel-toggle-left-view-window)
;;(global-set-key [f11] 'ide-skel-toggle-bottom-view-window)
;;(global-set-key [f12] 'ide-skel-toggle-right-view-window)
;;(global-set-key [C-next] 'tabbar-backward)
;;(global-set-key [C-prior]  'tabbar-forward)
;;(global-set-key [(meta return)] 'semantic-ia-complete-symbol-menu)
;;(global-set-key [C-\;] 'ecb-goto-window-edit-last)
;;(global-set-key [C-\'] 'ecb-goto-window-methods)
;;(global-set-key [C-.] 'cscope-find-global-definition)
;;(global-set-key [C-,] 'cscope-pop-mark)
(enable-visual-studio-bookmarks)
(add-hook 'c-mode-common-hook ( lambda() ( c-set-style "k&r" ) ) )
(add-hook 'c++-mode-common-hook ( lambda() ( c-set-style "k&r" ) ) )
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(delete-selection-mode nil)
 '(ecb-options-version "2.32")
 '(scroll-bar-mode (quote right)))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(tabbar-button-highlight ((t (:inherit tabbar-button))))
 '(tabbar-default ((t (:inherit variable-pitch :background "gray82" :foreground "gray50" :height 0.8))))
 '(tabbar-highlight ((t nil)))
 '(tabbar-selected ((t (:inherit tabbar-default :background "white" :foreground "blue" :box (:line-width 1 :color "black")))))
 '(tabbar-separator ((t (:inherit tabbar-default :height 0.2))))
 '(tabbar-unselected ((t (:inherit tabbar-default :background "gray72" :foreground "black" :box (:line-width 1 :color "black"))))))
