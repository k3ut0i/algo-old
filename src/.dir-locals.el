((c-mode .
	 ((eval .
		 (progn
		   (add-to-list 'flycheck-gcc-include-path (expand-file-name "../include"))
		   (add-to-list 'flycheck-clang-include-path  (expand-file-name "../include")))))))
