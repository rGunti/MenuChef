<?php
class AppDocumentRequest extends BaseRequest {
    /** @return string */
    public function getPageContent() { return $this->getStorageValue('AppDocument_Content'); }

    /** @param $content string */
    private function setPageContent($content) { $this->setStorageValue('AppDocument_Content', $content); }

    /** @return string */
    private function getUsedPageTitle() { return $this->getStorageValue('AppDocument_Title'); }

    /** @param $title string */
    private function setUsedPageTitle($title) { $this->setStorageValue('AppDocument_Title', $title); }

    /** @return string */
    public function getFormPath() { return '_doc.inc'; }

    /** @return string */
    public function getPageTitle() { return $this->getUsedPageTitle(); }

    /**
     * Method called then request gets processed
     * @param string $path Current Navigation Path
     * @param array $get
     * @param array $post
     * @return mixed
     */
    public function process($path, $get = [], $post = []) {
        if (PathUtils::pathMatches($path, '/_Docs')) {
            $this->setUsedPageTitle(t('app_documents_title'));
        } else if (PathUtils::pathMatches($path, '/_Docs/ToS')) {
            $this->setPageContent(t('tos_full_content'));
            $this->setUsedPageTitle(t('tos_title'));
        } else if (PathUtils::pathMatches($path, '/_Docs/Imprint')) {
            $this->setPageContent(t('imprint_full_content'));
            $this->setUsedPageTitle(t('imprint_title'));
        } else if (PathUtils::pathMatches($path, '/_Docs/Copyright')) {
            $this->setPageContent(t('copyright_full_content'));
            $this->setUsedPageTitle(t('copyright_title'));
        } else {
            AppUtils::clearRenderedContent();
            PathUtils::internalRedirect('/_Docs');
        }
    }
}
